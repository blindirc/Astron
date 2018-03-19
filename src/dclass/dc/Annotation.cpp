#include <iostream>

#include "Annotation.h"
#include "ArrayType.h"
#include "DistributedType.h"
#include "Field.h"
#include "Parameter.h"
#include "Method.h"
#include "NumericType.h"


namespace dclass   // open namespace
{

static uint64_t extract_parameter_size(Parameter *parameter);
static uint64_t extract_method_args_size(Method *method);

static uint64_t
extract_parameter_size(Parameter *parameter)
{
    if (!parameter) return 0;

    DistributedType *type = parameter->get_type();
    ArrayType *array_data = type->as_array();

    if (array_data) {
        DistributedType *distributed_type = array_data->get_element_type();
        uint64_t max_range = array_data->get_range().max.uinteger;
        uint64_t element_size = distributed_type->get_size();

        uint64_t bytes = max_range * element_size;
        return bytes;
    }

    return type->get_size();
}

static uint64_t
extract_method_args_size(Method *method)
{
    if (!method) return 0;

    const size_t max_params = method->get_num_parameters();
    for (size_t ii = 0; ii < max_params; ii++) {
        Parameter *parameter = method->get_parameter(ii);
        return extract_parameter_size(parameter);
    }

    return 0;
}

bool
Annotation::check_size_lt()
{
    uint64_t bytes = 0;
    bool dead = false;

    // Walk through each field
    for (const auto& field : this->m_fields) {
        DistributedType *type = field->get_type();
        bytes += type ? type->get_size() : 0;

        Method *method = type->as_method();
        uint64_t tmp_bytes = extract_method_args_size(method);
        bytes += tmp_bytes;

        if (tmp_bytes > this->check_max_bytes || bytes > this->check_max_bytes) {
            std::cerr << "annotation failure: field " << field->get_name()
                << " required an additional " << tmp_bytes << " bytes, overflowing to "
                << bytes << " bytes.\n";

            dead = true;
        }
    }

    if (dead)
        std::cerr << "@check_size_lt " << this->check_max_bytes << " failed, aborting.\n";

    return !dead;
}

bool
Annotation::validate_dclass(std::vector<Field *> fields)
{
    this->m_fields = fields;
    std::cout << "annotation: Validating dclass " << this->m_dclass_name << "...\n";

    switch (this->m_annotation_type) {
        case AnnotationType::CHECK_SIZE_LT:
            return this->check_size_lt();
        default:
            std::cerr << "Invalid annotation\n";
            return false;
    }
}

}
