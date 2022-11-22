#include <gtest/gtest.h>
#include <toad/data_reader/environment_variable/ParseEnvironmentVariable.hh>

class ParseCorrectFormatForEnvironmentVariable : public testing::TestWithParam<std::string>
{
};

TEST_P(ParseCorrectFormatForEnvironmentVariable, dsa)
{
    auto input = GetParam();
    EXPECT_TRUE(toad::data_reader::parser::isCorrectFormat(input));
}

INSTANTIATE_TEST_SUITE_P(StandardCorrectFormatForEnvironmentVariables,
                         ParseCorrectFormatForEnvironmentVariable,
                         testing::Values("${var_name}",
                                         "${varname}",
                                         "${var_name} ",
                                         " ${var_name}",
                                         " ${1231var_name23}",
                                         " ${1var_na123me}   ",
                                         "  ${1var_name} ",
                                         "  ${1varname} "));

INSTANTIATE_TEST_SUITE_P(SyntaxForOptionalParameterIsCorrect,
                         ParseCorrectFormatForEnvironmentVariable,
                         testing::Values("${var_name:asd}",
                                         "${varname:asd_asd}",
                                         "${var_name:_asd} ",
                                         " ${var_name:das_}",
                                         " ${1231var_name23:ad}",
                                         " ${1var_:na123me}   ",
                                         "  ${1var:_name} ",
                                         "  ${1var:name} "));

INSTANTIATE_TEST_SUITE_P(SyntaxForMandatoryParameterIsCorrect,
                         ParseCorrectFormatForEnvironmentVariable,
                         testing::Values("${var_name:?asd asd a?}",
                                         "${varname:?asd_asd as da}",
                                         "${var_name:?_asdasd a? as? a?} ",
                                         " ${var_name:?das_ ?  asd}",
                                         " ${1231var_name23:??  adsad}",
                                         " ${1var_:?na123me?Adsad}   ",
                                         "  ${1var:?_name:?!Adasd} ",
                                         "  ${1var:?nameasd asd a da as ad ad} "));

class ParseIncorrectFormatForEnvironmentVariable : public testing::TestWithParam<std::string>
{
};

TEST_P(ParseIncorrectFormatForEnvironmentVariable, asd)
{
    auto input = GetParam();
    EXPECT_FALSE(toad::data_reader::parser::isCorrectFormat(input));
}

INSTANTIATE_TEST_SUITE_P(StandardIncorrectFormatForEnvironmentVariables,
                         ParseIncorrectFormatForEnvironmentVariable,
                         testing::Values("${var_name",
                                         "$varname}",
                                         "{var_name} ",
                                         " $var_name",
                                         " 1231var_name23}",
                                         "${var name}",
                                         "${ var_name}",
                                         "${var_name }",
                                         "${ var_name }"
                                         "${ var name }"));

INSTANTIATE_TEST_SUITE_P(SyntaxForOptionalParameterIsIncorrect,
                         ParseIncorrectFormatForEnvironmentVariable,
                         testing::Values("${var_name:}",
                                         "${var name:asd}",
                                         "${var_name:asd",
                                         "$varn:ame}",
                                         "{var:name} ",
                                         " $var:",
                                         " 1231var:name23}",
                                         "${var: name}",
                                         "${var :name}",
                                         "${var : name}",
                                         "${ var:name}",
                                         "${var:name }",
                                         "${ var:name }"
                                         "${ var:name }"
                                         "${ :name }"
                                         "${:name }"
                                         ":name }"
                                         "${ var:"
                                         "${ var: "));