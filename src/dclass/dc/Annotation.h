// Filename: Annotation.h
#pragma once
#include <string>
#include <vector>

#include "KeywordList.h"

namespace dclass   // open namespace dclass
{

class Field;
class Method;
class Parameter;

enum struct AnnotationType {
    INVALID,
    CHECK_SIZE_LT,
};

// An Annotation specifies a run-time analyses on a
// dclass
struct Annotation final : public KeywordList
{
    AnnotationType m_annotation_type = AnnotationType::INVALID;
    std::string m_annotation_name;
    std::string m_dclass_name;

    bool check_size_lt();
    bool validate_dclass(std::vector<Field *> fields);
    std::string get_name() const { return this->m_annotation_name; }

    unsigned int check_max_bytes = 0;
    std::vector<Field *> m_fields;
};

}
