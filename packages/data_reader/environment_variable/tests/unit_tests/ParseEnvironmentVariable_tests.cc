#include <gtest/gtest.h>
#include <toad/data_reader/environment_variable/ParseEnvironmentVariable.hh>

class ParseEnvironmentVariableFormat : public testing::TestWithParam<std::string>
{
};

class ParseCorrectFormatForPlainEnvironmentVariable : public ParseEnvironmentVariableFormat
{
};

TEST_P(ParseCorrectFormatForPlainEnvironmentVariable,
       inputBeginningWithDollarSignAndValuesWithoutWhitespaceBetweenBracesShouldBeCorrectFormat)
{
    auto input = GetParam();
    EXPECT_TRUE(toad::data_reader::parser::isCorrectFormat(input));
}

INSTANTIATE_TEST_SUITE_P(StandardCorrectFormatForEnvironmentVariables,
                         ParseCorrectFormatForPlainEnvironmentVariable,
                         testing::Values("${var_name}",
                                         "${varname}",
                                         "${var_name} ",
                                         " ${var_name}",
                                         " ${1231var_name23}",
                                         " ${1var_na123me}   ",
                                         "  ${1var_name} ",
                                         "  ${1varname} "));

class ParseCorrectFormatForOptionalEnvironmentVariable : public ParseEnvironmentVariableFormat
{
};

TEST_P(ParseCorrectFormatForOptionalEnvironmentVariable,
       inputBeginningWithDollarSignAndTwoValuesSeparatedByColonWithNoWhitespaceBetweenBracesShouldBeCorrectFormat)
{
    auto input = GetParam();
    EXPECT_TRUE(toad::data_reader::parser::isCorrectFormat(input));
}

INSTANTIATE_TEST_SUITE_P(SyntaxForOptionalParameterIsCorrect,
                         ParseCorrectFormatForOptionalEnvironmentVariable,
                         testing::Values("${var_name:asd}",
                                         "${varname:asd_asd}",
                                         "${var_name:_asd} ",
                                         " ${var_name:das_}",
                                         " ${1231var_name23:ad}",
                                         " ${1var_:na123me}   ",
                                         "  ${1var:_name} ",
                                         "  ${1var:name} "));

class ParseCorrectFormatForMandatoryEnvironmentVariable : public ParseEnvironmentVariableFormat
{
};

TEST_P(
    ParseCorrectFormatForMandatoryEnvironmentVariable,
    inputStartingWithDollarSignAndTwoValuesSeparatedByColonAndcharacterBetweenBracesOfWhichLeftValueMustBeWithoutWhitespaceShouldBeCorrectFormat)
{
    auto input = GetParam();
    EXPECT_TRUE(toad::data_reader::parser::isCorrectFormat(input));
}

INSTANTIATE_TEST_SUITE_P(SyntaxForMandatoryParameterIsCorrect,
                         ParseCorrectFormatForMandatoryEnvironmentVariable,
                         testing::Values("${var_name:?asd asd a?}",
                                         "${varname:?asd_asd as da}",
                                         "${var_name:?_asdasd a? as? a?} ",
                                         " ${var_name:?das_ ?  asd}",
                                         " ${1231var_name23:??  adsad}",
                                         " ${1var_:?na123me?Adsad}   ",
                                         "  ${1var:?_name:?!Adasd} ",
                                         "  ${1var:?} ",
                                         "  ${1var:? } ",
                                         "  ${1var:?nameasd asd a da as ad ad} "));

class ParseIncorrectFormatForPlainEnvironmentVariable : public ParseEnvironmentVariableFormat
{
};

TEST_P(
    ParseIncorrectFormatForPlainEnvironmentVariable,
    inputWithoutDollarSignAtBeginningOrWithIncompleteSetOfBracesOrWithValueThatHasWhiteFormatCharacterShouldBeConsideredInvalid)
{
    auto input = GetParam();
    EXPECT_FALSE(toad::data_reader::parser::isCorrectFormat(input));
}

INSTANTIATE_TEST_SUITE_P(StandardIncorrectFormatForEnvironmentVariables,
                         ParseIncorrectFormatForPlainEnvironmentVariable,
                         testing::Values("${var_name",
                                         "$varname}",
                                         "{var_name} ",
                                         " $var_name",
                                         " 1231var_name23}",
                                         "${var name}",
                                         "${ var_name}",
                                         "${var_name }",
                                         "${ var_name }",
                                         "${ var name }"));

class ParseIncorrectFormatForOptionalEnvironmentVariable : public ParseEnvironmentVariableFormat
{
};

TEST_P(
    ParseIncorrectFormatForOptionalEnvironmentVariable,
    inputWithoutDollarSignAtBeginningOrIncompleteSetOfBracketsOrValuesWithWhitespaceOrWithoutValuesAfterOrBeforeColonShouldBeIncorrectFormate)
{
    auto input = GetParam();
    EXPECT_FALSE(toad::data_reader::parser::isCorrectFormat(input));
}

INSTANTIATE_TEST_SUITE_P(SyntaxForOptionalParameterIsIncorrect,
                         ParseIncorrectFormatForOptionalEnvironmentVariable,
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
                                         "${ var:name }",
                                         "${ var:name }",
                                         "${ :name }",
                                         "${:name }",
                                         ":name }",
                                         "${ var:",
                                         "${ var: "));

class ParseIncorrectFormatForMandatoryEnvironmentVariable : public ParseEnvironmentVariableFormat
{
};

TEST_P(
    ParseIncorrectFormatForMandatoryEnvironmentVariable,
    inputWithoutDollarSignAtBeginningOrIncompleteSetOfBracesOrValueOnLeftWithWhiteSpacesOrNoValueBeforeColonAndQuestionMarkShouldBeInvalidFormat)
{
    auto input = GetParam();
    EXPECT_FALSE(toad::data_reader::parser::isCorrectFormat(input));
}

INSTANTIATE_TEST_SUITE_P(SyntaxForMandatoryParameterIsIncorrect,
                         ParseIncorrectFormatForMandatoryEnvironmentVariable,
                         testing::Values("${var_name :?}",
                                         "${var name:?asd}",
                                         "${var_name:?asd",
                                         "$var:?ame}",
                                         "{var:?name} ",
                                         " $var:?",
                                         " 1231var:?name23}",
                                         "${var name:? name}",
                                         "${var :?name}",
                                         "${var :? name}",
                                         "${ var:?name}",
                                         "${ var:?name }",
                                         "${ var:?name }",
                                         "${ :?name }",
                                         "${:?name }",
                                         ":?name }",
                                         "${ var:?",
                                         "${       var :? asd}",
                                         "${       var :? "));