#include "gtest\gtest.h"
#include "AttributeCompatibility.h"
#include "GfcSchema/EntityAttribute.h"
#include "GfcSchema/BuildinType.h"
#include "GfcSchema/EnumType.h"
#include "GfcSchema/EntityClass.h"
#include "Converter.h"
#include "GfcEngine\Property.h"
#include "GfcEngine\PropValue.h"

using namespace gfc::schema;
using namespace gfc::engine;

TEST(TestAttributeCompatibility, FromIsNil)
{
    gfc::schema::CAttribute oToAttrib;
    oToAttrib.SetName(L"abc");
    CAttributeCompatibility oCompatibility;
    oCompatibility.init(nullptr, &oToAttrib, 0);
    EXPECT_EQ(true, L"abc" == oCompatibility.getName());
    EXPECT_EQ(false, oCompatibility.isCompatible());
    EXPECT_EQ(nullptr, oCompatibility.converter());
}

TEST(TestAttributeCompatibility, FromIsNil_ToOptional)
{
    gfc::schema::CAttribute oToAttrib;
    oToAttrib.SetOptionalFlag(true);
    CAttributeCompatibility oCompatibility;
    oCompatibility.init(nullptr, &oToAttrib, 0);
    EXPECT_EQ(true, oCompatibility.isCompatible());
}

TEST(TestAttributeCompatibility, FromIsNil_ToRepeat)
{
    gfc::schema::CAttribute oToAttrib;
    oToAttrib.SetRepeatFlag(true);
    CAttributeCompatibility oCompatibility;
    oCompatibility.init(nullptr, &oToAttrib, 0);
    EXPECT_EQ(true, oCompatibility.isCompatible());
}

TEST(TestAttributeCompatibility, ToIsNil)
{
    gfc::schema::CAttribute oFromAttrib;
    oFromAttrib.SetName(L"abc");
    CAttributeCompatibility oCompatibility;
    oCompatibility.init(&oFromAttrib, nullptr, -1);
    EXPECT_EQ(true, L"abc" == oCompatibility.getName());
    EXPECT_EQ(true, oCompatibility.isCompatible());
    EXPECT_EQ(nullptr, oCompatibility.converter());
}

TEST(TestAttributeCompatibility, getTypeCompatibility_Bool_Int)
{
    gfc::schema::CBooleanType oFrom;
    gfc::schema::CIntegerType oTo;
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(true, oTypeCompatibility.isCompatibility);
    BooleanValue oFromValue;
    IntegerValue oIntValue;
    oFromValue.setAsBoolean(true);
    oTypeCompatibility.converter->transform(&oFromValue, &oIntValue);
    EXPECT_EQ(1, oIntValue.asInteger());
}

TEST(TestAttributeCompatibility, getTypeCompatibility_Bool_Bool)
{
    gfc::schema::CBooleanType oFrom;
    gfc::schema::CBooleanType oTo;
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(true, oTypeCompatibility.isCompatibility);
    BooleanValue oFromValue;
    BooleanValue oIntValue;
    oFromValue.setAsBoolean(true);
    oTypeCompatibility.converter->transform(&oFromValue, &oIntValue);
    EXPECT_EQ(true, oIntValue.asBoolean());
}

TEST(TestAttributeCompatibility, getTypeCompatibility_Bool_Real)
{
    gfc::schema::CBooleanType oFrom;
    gfc::schema::CRealType oTo;
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(true, oTypeCompatibility.isCompatibility);
    BooleanValue oFromValue;
    DoubleValue oIntValue;
    oFromValue.setAsBoolean(true);
    oTypeCompatibility.converter->transform(&oFromValue, &oIntValue);
    auto dVal = oIntValue.asDouble();
    EXPECT_NEAR(1.0, dVal, 1e-6);
}

TEST(TestAttributeCompatibility, getTypeCompatibility_Bool_String)
{
    gfc::schema::CBooleanType oFrom;
    gfc::schema::CStringType oTo;
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(true, oTypeCompatibility.isCompatibility);
    BooleanValue oFromValue;
    StringValue oToValue;
    oFromValue.setAsBoolean(true);
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(true, "1" == oToValue.asString());
}

TEST(TestAttributeCompatibility, getTypeCompatibility_Bool_Enum)
{
    gfc::schema::CBooleanType oFrom;
    gfc::schema::CEnumType oTo;
    oTo.addEnum(L"abc", L"");
    oTo.addEnum(L"def", L"");
    oTo.addEnum(L"hig", L"");
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(true, oTypeCompatibility.isCompatibility);
    BooleanValue oFromValue;
    IntegerValue oToValue;
    oFromValue.setAsBoolean(true);
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(1, oToValue.asInteger());
}

TEST(TestAttributeCompatibility, getTypeCompatibility_Bool_Entity)
{
    gfc::schema::CBooleanType oFrom;
    gfc::schema::CClass oTo(L"CTest");
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(false, oTypeCompatibility.isCompatibility);
    BooleanValue oFromValue;
    EntityRefValue oToValue;
    oFromValue.setAsBoolean(true);
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(true, oToValue.isNull());
}
TEST(TestAttributeCompatibility, getTypeCompatibility_Int_Bool)
{
    gfc::schema::CIntegerType oFrom;
    gfc::schema::CBooleanType oTo;
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(true, oTypeCompatibility.isCompatibility);
    IntegerValue oFromValue;
    BooleanValue oToValue;
    oFromValue.setAsInteger(12);
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(false, oToValue.isNull());
    EXPECT_EQ(true, oToValue.asBoolean());
}

TEST(TestAttributeCompatibility, getTypeCompatibility_Int_Int)
{
    gfc::schema::CIntegerType oFrom;
    gfc::schema::CIntegerType oTo;
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(true, oTypeCompatibility.isCompatibility);
    IntegerValue oFromValue;
    IntegerValue oToValue;
    oFromValue.setAsInteger(12);
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(false, oToValue.isNull());
    EXPECT_EQ(12, oToValue.asInteger());
}

TEST(TestAttributeCompatibility, getTypeCompatibility_Int_Real)
{
    gfc::schema::CIntegerType oFrom;
    gfc::schema::CRealType oTo;
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(true, oTypeCompatibility.isCompatibility);
    IntegerValue oFromValue;
    DoubleValue oToValue;
    oFromValue.setAsInteger(12);
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(false, oToValue.isNull());
    EXPECT_NEAR(12, oToValue.asDouble(), 1e-7);
}

TEST(TestAttributeCompatibility, getTypeCompatibility_Int_String)
{
    gfc::schema::CIntegerType oFrom;
    gfc::schema::CStringType oTo;
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(true, oTypeCompatibility.isCompatibility);
    IntegerValue oFromValue;
    StringValue oToValue;
    oFromValue.setAsInteger(12);
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(false, oToValue.isNull());
    EXPECT_EQ(12, std::stoi(oToValue.asString()));
}

TEST(TestAttributeCompatibility, getTypeCompatibility_Int_Enum)
{
    gfc::schema::CIntegerType oFrom;
    gfc::schema::CEnumType oTo;
    oTo.addEnum(L"abc", L"");
    oTo.addEnum(L"def", L"");
    oTo.addEnum(L"hig", L"");
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(true, oTypeCompatibility.isCompatibility);
    IntegerValue oFromValue;
    IntegerValue oToValue;
    oFromValue.setAsInteger(12);
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(false, oToValue.isNull());
    EXPECT_EQ(0, oToValue.asInteger());
}

TEST(TestAttributeCompatibility, getTypeCompatibility_Int_Entity)
{
    gfc::schema::CIntegerType oFrom;
    gfc::schema::CClass oTo(L"CTest");
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(false, oTypeCompatibility.isCompatibility);
    IntegerValue oFromValue;
    EntityRefValue oToValue;
    oFromValue.setAsInteger(12);
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(true, oToValue.isNull());
}

TEST(TestAttributeCompatibility, getTypeCompatibility_Real_Bool)
{
    gfc::schema::CRealType oFrom;
    gfc::schema::CBooleanType oTo;
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(false, oTypeCompatibility.isCompatibility);
    DoubleValue oFromValue;
    BooleanValue oToValue;
    oFromValue.setAsDouble(12.3);
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(true, oToValue.isNull());
}

TEST(TestAttributeCompatibility, getTypeCompatibility_Real_Int)
{
    gfc::schema::CRealType oFrom;
    gfc::schema::CIntegerType oTo;
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(false, oTypeCompatibility.isCompatibility);
    DoubleValue oFromValue;
    IntegerValue oToValue;
    oFromValue.setAsDouble(12.3);
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(true, oToValue.isNull());
}

TEST(TestAttributeCompatibility, getTypeCompatibility_Real_Real)
{
    gfc::schema::CRealType oFrom;
    gfc::schema::CRealType oTo;
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(true, oTypeCompatibility.isCompatibility);
    DoubleValue oFromValue;
    DoubleValue oToValue;
    oFromValue.setAsDouble(12.3);
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(false, oToValue.isNull());
    EXPECT_NEAR(12.3, oToValue.asDouble(), 1e-7);
}

TEST(TestAttributeCompatibility, getTypeCompatibility_Real_String)
{
    gfc::schema::CRealType oFrom;
    gfc::schema::CStringType oTo;
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(true, oTypeCompatibility.isCompatibility);
    DoubleValue oFromValue;
    StringValue oToValue;
    oFromValue.setAsDouble(12.3);
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(false, oToValue.isNull());
    EXPECT_NEAR(12.3, std::stod(oToValue.asString()), 1e-7);
}

TEST(TestAttributeCompatibility, getTypeCompatibility_Real_Enum)
{
    gfc::schema::CRealType oFrom;
    gfc::schema::CEnumType oTo;
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(false, oTypeCompatibility.isCompatibility);
    DoubleValue oFromValue;
    IntegerValue oToValue;
    oFromValue.setAsDouble(12.3);
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(true, oToValue.isNull());
}

TEST(TestAttributeCompatibility, getTypeCompatibility_Real_Entity)
{
    gfc::schema::CRealType oFrom;
    gfc::schema::CClass oTo;
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(false, oTypeCompatibility.isCompatibility);
    DoubleValue oFromValue;
    EntityRefValue oToValue;
    oFromValue.setAsDouble(12.3);
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(true, oToValue.isNull());
}

TEST(TestAttributeCompatibility, getTypeCompatibility_String_bool)
{
    gfc::schema::CStringType oFrom;
    gfc::schema::CBooleanType oTo;
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(false, oTypeCompatibility.isCompatibility);
    StringValue oFromValue;
    BooleanValue oToValue;
    oFromValue.setAsString(".T.");
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(true, oToValue.isNull());
}

TEST(TestAttributeCompatibility, getTypeCompatibility_String_Int)
{
    gfc::schema::CStringType oFrom;
    gfc::schema::CIntegerType oTo;
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(false, oTypeCompatibility.isCompatibility);
    StringValue oFromValue;
    IntegerValue oToValue;
    oFromValue.setAsString("12");
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(true, oToValue.isNull());
}

TEST(TestAttributeCompatibility, getTypeCompatibility_String_Real)
{
    gfc::schema::CStringType oFrom;
    gfc::schema::CRealType oTo;
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(false, oTypeCompatibility.isCompatibility);
    StringValue oFromValue;
    DoubleValue oToValue;
    oFromValue.setAsString("12.3");
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(true, oToValue.isNull());
}

TEST(TestAttributeCompatibility, getTypeCompatibility_String_String)
{
    gfc::schema::CStringType oFrom;
    gfc::schema::CStringType oTo;
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(true, oTypeCompatibility.isCompatibility);
    StringValue oFromValue;
    StringValue oToValue;
    oFromValue.setAsString("sdafasd");
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(false, oToValue.isNull());
    EXPECT_STREQ("sdafasd", oToValue.asString().c_str());
}

TEST(TestAttributeCompatibility, getTypeCompatibility_String_Enum)
{
    gfc::schema::CStringType oFrom;
    gfc::schema::CEnumType oTo;
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(false, oTypeCompatibility.isCompatibility);
    StringValue oFromValue;
    IntegerValue oToValue;
    oFromValue.setAsString("12");
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(true, oToValue.isNull());
}

TEST(TestAttributeCompatibility, getTypeCompatibility_String_Entity)
{
    gfc::schema::CStringType oFrom;
    gfc::schema::CClass oTo;
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(false, oTypeCompatibility.isCompatibility);
    StringValue oFromValue;
    EntityRefValue oToValue;
    oFromValue.setAsString("12");
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(true, oToValue.isNull());
}

TEST(TestAttributeCompatibility, getTypeCompatibility_Enum_Bool)
{
    gfc::schema::CEnumType oFrom;
    oFrom.addEnum(L"abc", L"");
    oFrom.addEnum(L"def", L"");
    oFrom.addEnum(L"hig", L"");
    gfc::schema::CBooleanType oTo;
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(true, oTypeCompatibility.isCompatibility);
    IntegerValue oFromValue;
    BooleanValue oToValue;
    oFromValue.setAsInteger(1);
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(false, oToValue.isNull());
    EXPECT_EQ(true, oToValue.asBoolean());
}

TEST(TestAttributeCompatibility, getTypeCompatibility_Enum_Int)
{
    gfc::schema::CEnumType oFrom;
    oFrom.addEnum(L"abc", L"");
    oFrom.addEnum(L"def", L"");
    oFrom.addEnum(L"hig", L"");
    gfc::schema::CIntegerType oTo;
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(true, oTypeCompatibility.isCompatibility);
    IntegerValue oFromValue;
    IntegerValue oToValue;
    oFromValue.setAsInteger(2);
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(false, oToValue.isNull());
    EXPECT_EQ(2, oToValue.asInteger());
}

TEST(TestAttributeCompatibility, getTypeCompatibility_Enum_Real)
{
    gfc::schema::CEnumType oFrom;
    oFrom.addEnum(L"abc", L"");
    oFrom.addEnum(L"def", L"");
    oFrom.addEnum(L"hig", L"");
    gfc::schema::CRealType oTo;
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(true, oTypeCompatibility.isCompatibility);
    IntegerValue oFromValue;
    IntegerValue oToValue;
    oFromValue.setAsInteger(2);
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(false, oToValue.isNull());
    EXPECT_NEAR(2, oToValue.asDouble(), 1e-7);
}

TEST(TestAttributeCompatibility, getTypeCompatibility_Enum_Enum_1)
{
    gfc::schema::CEnumType oFrom;
    oFrom.addEnum(L"abc", L"");
    oFrom.addEnum(L"def", L"");
    oFrom.addEnum(L"hig", L"");
    gfc::schema::CEnumType oTo;
    oTo.addEnum(L"abc", L"");
    oTo.addEnum(L"def", L"");
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(false, oTypeCompatibility.isCompatibility);
    IntegerValue oFromValue;
    IntegerValue oToValue;
    oFromValue.setAsInteger(2);
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(true, oToValue.isNull());

    oFromValue.setAsInteger(0);
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(false, oToValue.isNull());
    EXPECT_EQ(0, oToValue.asInteger());
}

TEST(TestAttributeCompatibility, getTypeCompatibility_Enum_Enum_2)
{
    gfc::schema::CEnumType oFrom;
    oFrom.addEnum(L"abc", L"");
    oFrom.addEnum(L"def", L"");
    oFrom.addEnum(L"hig", L"");
    gfc::schema::CEnumType oTo;
    oTo.addEnum(L"abc", L"");
    oTo.addEnum(L"def", L"");
    oTo.addEnum(L"hig", L"");
    oTo.addEnum(L"klm", L"");
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(true, oTypeCompatibility.isCompatibility);
    IntegerValue oFromValue;
    IntegerValue oToValue;
    oFromValue.setAsInteger(2);
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(false, oToValue.isNull());
    EXPECT_EQ(2, oToValue.asInteger());
}

TEST(TestAttributeCompatibility, getTypeCompatibility_Enum_Enum_3)
{
    gfc::schema::CEnumType oFrom;
    oFrom.addEnum(L"abc", L"");
    oFrom.addEnum(L"def", L"");
    oFrom.addEnum(L"hig", L"");
    gfc::schema::CEnumType oTo;
    oTo.addEnum(L"hig", L"");
    oTo.addEnum(L"abc", L"");
    oTo.addEnum(L"def", L"");
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(true, oTypeCompatibility.isCompatibility);
    IntegerValue oFromValue;
    IntegerValue oToValue;
    oFromValue.setAsInteger(2);
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(false, oToValue.isNull());
    EXPECT_EQ(0, oToValue.asInteger());
}

TEST(TestAttributeCompatibility, getTypeCompatibility_Enum_Class)
{
    gfc::schema::CEnumType oFrom;
    oFrom.addEnum(L"abc", L"");
    oFrom.addEnum(L"def", L"");
    oFrom.addEnum(L"hig", L"");
    gfc::schema::CClass oTo;
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(false, oTypeCompatibility.isCompatibility);
    IntegerValue oFromValue;
    EntityRefValue oToValue;
    oFromValue.setAsInteger(2);
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(true, oToValue.isNull());
}

TEST(TestAttributeCompatibility, getTypeCompatibility_Class_Bool)
{
    gfc::schema::CClass oFrom;
    gfc::schema::CBooleanType oTo;
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(false, oTypeCompatibility.isCompatibility);
    EntityRefValue oFromValue;
    BooleanValue oToValue;
    oFromValue.setAsEntityRef(2);
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(true, oToValue.isNull());
}

TEST(TestAttributeCompatibility, getTypeCompatibility_Class_Int)
{
    gfc::schema::CClass oFrom;
    gfc::schema::CIntegerType oTo;
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(false, oTypeCompatibility.isCompatibility);
    EntityRefValue oFromValue;
    IntegerValue oToValue;
    oFromValue.setAsEntityRef(2);
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(true, oToValue.isNull());
}

TEST(TestAttributeCompatibility, getTypeCompatibility_Class_Real)
{
    gfc::schema::CClass oFrom;
    gfc::schema::CRealType oTo;
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(false, oTypeCompatibility.isCompatibility);
    EntityRefValue oFromValue;
    DoubleValue oToValue;
    oFromValue.setAsEntityRef(2);
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(true, oToValue.isNull());
}

TEST(TestAttributeCompatibility, getTypeCompatibility_Class_String)
{
    gfc::schema::CClass oFrom;
    gfc::schema::CStringType oTo;
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(false, oTypeCompatibility.isCompatibility);
    EntityRefValue oFromValue;
    StringValue oToValue;
    oFromValue.setAsEntityRef(2);
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(true, oToValue.isNull());
}

TEST(TestAttributeCompatibility, getTypeCompatibility_Class_Enum)
{
    gfc::schema::CClass oFrom;
    gfc::schema::CEnumType oTo;
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(false, oTypeCompatibility.isCompatibility);
    EntityRefValue oFromValue;
    IntegerValue oToValue;
    oFromValue.setAsEntityRef(2);
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(true, oToValue.isNull());
}

TEST(TestAttributeCompatibility, getTypeCompatibility_Class_Class)
{
    gfc::schema::CClass oFrom(L"CTest");
    gfc::schema::CClass oTo(L"CTest");
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(true, oTypeCompatibility.isCompatibility);
    EntityRefValue oFromValue;
    EntityRefValue oToValue;
    oFromValue.setAsEntityRef(2);
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(false, oToValue.isNull());
    EXPECT_EQ(2, oToValue.asEntityRef());
}

TEST(TestAttributeCompatibility, getTypeCompatibility_Class_Class_1)
{
    gfc::schema::CClass oFrom(L"CTest");
    gfc::schema::CClass oTo(L"CTest2");
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(false, oTypeCompatibility.isCompatibility);
    EntityRefValue oFromValue;
    EntityRefValue oToValue;
    oFromValue.setAsEntityRef(2);
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(true, oToValue.isNull());
}

TEST(TestAttributeCompatibility, getTypeCompatibility_Class_Class_2)
{
    gfc::schema::CClass oParent2(L"CTest2");
    gfc::schema::CClass oParent(L"CTest1");
    gfc::schema::CClass oFrom(L"CTest");
    gfc::schema::CClass oTo(L"CTest2");
    oFrom.setParent(&oParent);
    oParent.setParent(&oParent2);
    auto oTypeCompatibility = CAttributeCompatibility::getTypeCompatibility(&oFrom, &oTo);
    EXPECT_EQ(true, oTypeCompatibility.isCompatibility);
    EntityRefValue oFromValue;
    EntityRefValue oToValue;
    oFromValue.setAsEntityRef(2);
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(false, oToValue.isNull());
    EXPECT_EQ(2, oToValue.asEntityRef());
}

TEST(TestAttributeCompatibility, getMultiCompatibility_Array_Array)
{
    gfc::schema::CIntegerType oIntegerType;
    gfc::schema::CAttribute oFromAttribute;
    oFromAttribute.SetType(&oIntegerType);
    oFromAttribute.SetRepeatFlag(true);
    gfc::schema::CAttribute oToAttribute;
    oToAttribute.SetType(&oIntegerType);
    oToAttribute.SetRepeatFlag(true);
    auto oTypeCompatibility2 = CAttributeCompatibility::getTypeCompatibility(&oIntegerType, &oIntegerType);
    auto oTypeCompatibility = CAttributeCompatibility::getMultiCompatibility(&oFromAttribute, &oToAttribute);
    oTypeCompatibility.converter->setNext(oTypeCompatibility2.converter->clone());
    oTypeCompatibility.converter->init(&oIntegerType, &oIntegerType);
    EXPECT_EQ(true, oTypeCompatibility.isCompatibility);
//    std::wstring sValue = L"(1,2,3)";
    CompositePropValue oFromValue;
    oFromValue.add(new IntegerValue(1));
    oFromValue.add(new IntegerValue(2));
    oFromValue.add(new IntegerValue(3));
    CompositePropValue oToValue;
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(3, oToValue.getCount());
    EXPECT_EQ(1, oToValue.getItems(0)->asInteger());
    EXPECT_EQ(2, oToValue.getItems(1)->asInteger());
    EXPECT_EQ(3, oToValue.getItems(2)->asInteger());
}

TEST(TestAttributeCompatibility, getMultiCompatibility_Array_Optional)
{
    gfc::schema::CIntegerType oIntegerType;
    gfc::schema::CAttribute oFromAttribute;
    oFromAttribute.SetType(&oIntegerType);
    oFromAttribute.SetRepeatFlag(true);
    gfc::schema::CAttribute oToAttribute;
    oToAttribute.SetType(&oIntegerType);
    oToAttribute.SetOptionalFlag(true);
    auto oTypeCompatibility2 = CAttributeCompatibility::getTypeCompatibility(&oIntegerType, &oIntegerType);
    auto oTypeCompatibility = CAttributeCompatibility::getMultiCompatibility(&oFromAttribute, &oToAttribute);
    oTypeCompatibility.converter->setNext(oTypeCompatibility2.converter->clone());
    oTypeCompatibility.converter->init(&oIntegerType, &oIntegerType);
    EXPECT_EQ(true, oTypeCompatibility.isCompatibility);
//    std::wstring sValue = L"(1,2,3)";
    CompositePropValue oFromValue;
    oFromValue.add(new IntegerValue(1));
    oFromValue.add(new IntegerValue(2));
    oFromValue.add(new IntegerValue(3));
    IntegerValue oToValue;
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(false, oToValue.isNull());
    EXPECT_EQ(1, oToValue.asInteger());
}

TEST(TestAttributeCompatibility, getMultiCompatibility_Array_Required)
{
    gfc::schema::CIntegerType oIntegerType;
    gfc::schema::CAttribute oFromAttribute;
    oFromAttribute.SetType(&oIntegerType);
    oFromAttribute.SetRepeatFlag(true);
    gfc::schema::CAttribute oToAttribute;
    oToAttribute.SetType(&oIntegerType);
    auto oTypeCompatibility2 = CAttributeCompatibility::getTypeCompatibility(&oIntegerType, &oIntegerType);
    auto oTypeCompatibility = CAttributeCompatibility::getMultiCompatibility(&oFromAttribute, &oToAttribute);
    oTypeCompatibility.converter->setNext(oTypeCompatibility2.converter->clone());
    oTypeCompatibility.converter->init(&oIntegerType, &oIntegerType);
    EXPECT_EQ(false, oTypeCompatibility.isCompatibility);
    //    std::wstring sValue = L"(1,2,3)";
    CompositePropValue oFromValue;
    oFromValue.add(new IntegerValue(1));
    oFromValue.add(new IntegerValue(2));
    oFromValue.add(new IntegerValue(3));
    IntegerValue oToValue;
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(false, oToValue.isNull());
    EXPECT_EQ(1, oToValue.asInteger());
}

TEST(TestAttributeCompatibility, getMultiCompatibility_Array_Required_2)
{
    gfc::schema::CIntegerType oIntegerType;
    gfc::schema::CAttribute oFromAttribute;
    oFromAttribute.SetType(&oIntegerType);
    oFromAttribute.SetRepeatFlag(true);
    gfc::schema::CAttribute oToAttribute;
    oToAttribute.SetType(&oIntegerType);
    auto oTypeCompatibility2 = CAttributeCompatibility::getTypeCompatibility(&oIntegerType, &oIntegerType);
    auto oTypeCompatibility = CAttributeCompatibility::getMultiCompatibility(&oFromAttribute, &oToAttribute);
    oTypeCompatibility.converter->setNext(oTypeCompatibility2.converter->clone());
    oTypeCompatibility.converter->init(&oIntegerType, &oIntegerType);
    EXPECT_EQ(false, oTypeCompatibility.isCompatibility);
//    std::wstring sValue = L"()";
    CompositePropValue oFromValue;
    IntegerValue oToValue;
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(true, oToValue.isNull());
}

TEST(TestAttributeCompatibility, getMultiCompatibility_Optional_Array)
{
    gfc::schema::CIntegerType oIntegerType;
    gfc::schema::CAttribute oFromAttribute;
    oFromAttribute.SetType(&oIntegerType);
    oFromAttribute.SetOptionalFlag(true);
    gfc::schema::CAttribute oToAttribute;
    oToAttribute.SetType(&oIntegerType);
    oToAttribute.SetRepeatFlag(true);
    auto oTypeCompatibility2 = CAttributeCompatibility::getTypeCompatibility(&oIntegerType, &oIntegerType);
    auto oTypeCompatibility = CAttributeCompatibility::getMultiCompatibility(&oFromAttribute, &oToAttribute);
    oTypeCompatibility.converter->setNext(oTypeCompatibility2.converter->clone());
    oTypeCompatibility.converter->init(&oIntegerType, &oIntegerType);
    EXPECT_EQ(true, oTypeCompatibility.isCompatibility);
    {
        IntegerValue oFromValue;
        CompositePropValue oToValue;
        oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
        EXPECT_EQ(true, oToValue.isNull());
    }

    {
        IntegerValue oFromValue;
        oFromValue.setAsInteger(123);
        CompositePropValue oToValue;
        oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
        EXPECT_EQ(1, oToValue.getCount());
        EXPECT_EQ(123, oToValue.getItems(0)->asInteger());
    }
}

TEST(TestAttributeCompatibility, getMultiCompatibility_Optional_Optional)
{
    gfc::schema::CIntegerType oIntegerType;
    gfc::schema::CAttribute oFromAttribute;
    oFromAttribute.SetType(&oIntegerType);
    oFromAttribute.SetOptionalFlag(true);
    gfc::schema::CAttribute oToAttribute;
    oToAttribute.SetType(&oIntegerType);
    oToAttribute.SetOptionalFlag(true);
    auto oTypeCompatibility2 = CAttributeCompatibility::getTypeCompatibility(&oIntegerType, &oIntegerType);
    auto oTypeCompatibility = CAttributeCompatibility::getMultiCompatibility(&oFromAttribute, &oToAttribute);
    oTypeCompatibility.converter->setNext(oTypeCompatibility2.converter->clone());
    oTypeCompatibility.converter->init(&oIntegerType, &oIntegerType);
    EXPECT_EQ(true, oTypeCompatibility.isCompatibility);

    {
        IntegerValue oFromValue;
        IntegerValue oToValue;
        oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
        EXPECT_EQ(true, oToValue.isNull());
    }

    {
        IntegerValue oFromValue;
        oFromValue.setAsInteger(123);
        IntegerValue oToValue;
        oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
        EXPECT_EQ(123, oToValue.asInteger());
    }
}

TEST(TestAttributeCompatibility, getMultiCompatibility_Optional_Required)
{
    gfc::schema::CIntegerType oIntegerType;
    gfc::schema::CAttribute oFromAttribute;
    oFromAttribute.SetType(&oIntegerType);
    oFromAttribute.SetOptionalFlag(true);
    gfc::schema::CAttribute oToAttribute;
    oToAttribute.SetType(&oIntegerType);
    auto oTypeCompatibility2 = CAttributeCompatibility::getTypeCompatibility(&oIntegerType, &oIntegerType);
    auto oTypeCompatibility = CAttributeCompatibility::getMultiCompatibility(&oFromAttribute, &oToAttribute);
    oTypeCompatibility.converter->setNext(oTypeCompatibility2.converter->clone());
    oTypeCompatibility.converter->init(&oIntegerType, &oIntegerType);
    EXPECT_EQ(false, oTypeCompatibility.isCompatibility);
    {
        IntegerValue oFromValue;
        IntegerValue oToValue;
        oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
        EXPECT_EQ(true, oToValue.isNull());
    }

    {
        IntegerValue oFromValue;
        oFromValue.setAsInteger(123);
        IntegerValue oToValue;
        oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
        EXPECT_EQ(123, oToValue.asInteger());
    }
}

TEST(TestAttributeCompatibility, getMultiCompatibility_Required_Array)
{
    gfc::schema::CIntegerType oIntegerType;
    gfc::schema::CAttribute oFromAttribute;
    oFromAttribute.SetType(&oIntegerType);
    gfc::schema::CAttribute oToAttribute;
    oToAttribute.SetType(&oIntegerType);
    oToAttribute.SetRepeatFlag(true);
    auto oTypeCompatibility2 = CAttributeCompatibility::getTypeCompatibility(&oIntegerType, &oIntegerType);
    auto oTypeCompatibility = CAttributeCompatibility::getMultiCompatibility(&oFromAttribute, &oToAttribute);
    oTypeCompatibility.converter->setNext(oTypeCompatibility2.converter->clone());
    oTypeCompatibility.converter->init(&oIntegerType, &oIntegerType);
    EXPECT_EQ(true, oTypeCompatibility.isCompatibility);

    IntegerValue oFromValue;
    oFromValue.setAsInteger(123);
    CompositePropValue oToValue;
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(1, oToValue.getCount());
    EXPECT_EQ(123, oToValue.getItems(0)->asInteger());
}

TEST(TestAttributeCompatibility, getMultiCompatibility_Required_Optional)
{
    gfc::schema::CIntegerType oIntegerType;
    gfc::schema::CAttribute oFromAttribute;
    oFromAttribute.SetType(&oIntegerType);
    gfc::schema::CAttribute oToAttribute;
    oToAttribute.SetType(&oIntegerType);
    oToAttribute.SetOptionalFlag(true);
    auto oTypeCompatibility2 = CAttributeCompatibility::getTypeCompatibility(&oIntegerType, &oIntegerType);
    auto oTypeCompatibility = CAttributeCompatibility::getMultiCompatibility(&oFromAttribute, &oToAttribute);
    oTypeCompatibility.converter->setNext(oTypeCompatibility2.converter->clone());
    oTypeCompatibility.converter->init(&oIntegerType, &oIntegerType);
    EXPECT_EQ(true, oTypeCompatibility.isCompatibility);

    IntegerValue oFromValue;
    oFromValue.setAsInteger(123);
    IntegerValue oToValue;
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(123, oToValue.asInteger());
}

TEST(TestAttributeCompatibility, getMultiCompatibility_Required_Required)
{
    gfc::schema::CIntegerType oIntegerType;
    gfc::schema::CAttribute oFromAttribute;
    oFromAttribute.SetType(&oIntegerType);
    gfc::schema::CAttribute oToAttribute;
    oToAttribute.SetType(&oIntegerType);
    auto oTypeCompatibility2 = CAttributeCompatibility::getTypeCompatibility(&oIntegerType, &oIntegerType);
    auto oTypeCompatibility = CAttributeCompatibility::getMultiCompatibility(&oFromAttribute, &oToAttribute);
    oTypeCompatibility.converter->setNext(oTypeCompatibility2.converter->clone());
    oTypeCompatibility.converter->init(&oIntegerType, &oIntegerType);
    EXPECT_EQ(true, oTypeCompatibility.isCompatibility);

    IntegerValue oFromValue;
    oFromValue.setAsInteger(123);
    IntegerValue oToValue;
    oTypeCompatibility.converter->transform(&oFromValue, &oToValue);
    EXPECT_EQ(123, oToValue.asInteger());
}

/*
TEST(TestAttributeCompatibility, Compose)
{
    gfc::schema::CAttribute oFromAttrib;
    oFromAttrib.SetName(L"abc");
    oFromAttrib.SetRepeatFlag(true);
    gfc::schema::CEnumType oFrom;
    oFrom.addEnum(L"abc", L"");
    oFrom.addEnum(L"def", L"");
    oFrom.addEnum(L"hig", L"");
    oFromAttrib.SetType(&oFrom);
    gfc::schema::CAttribute oToAttrib;
    oToAttrib.SetRepeatFlag(true);
    gfc::schema::CIntegerType oTo;
    oToAttrib.SetType(&oTo);
    CAttributeCompatibility oCompatibility;
    oCompatibility.init(&oFromAttrib, &oToAttrib, -1);
    EXPECT_EQ(true, L"abc" == oCompatibility.getName());
    EXPECT_EQ(true, oCompatibility.isCompatible());
    //std::wstring sValue = L"(.abc.,.hig.,.abc.)";
    CAttributeValuePtr pValue(new CCompositeAttributeValue);
    pValue->add(CAttributeValuePtr(new CLeafAttributeValue(L".abc.")));
    pValue->add(CAttributeValuePtr(new CLeafAttributeValue(L".hig.")));
    pValue->add(CAttributeValuePtr(new CLeafAttributeValue(L".abc.")));
    oCompatibility.converter()->transform(pValue);
    EXPECT_EQ(true, L"(0,2,0)" == pValue->asString());
}

TEST(TestAttributeCompatibility, Compose_string)
{
    gfc::schema::CAttribute oFromAttrib;
    oFromAttrib.SetName(L"abc");
    oFromAttrib.SetRepeatFlag(true);
    gfc::schema::CStringType oFrom;
    oFromAttrib.SetType(&oFrom);
    gfc::schema::CAttribute oToAttrib;
    oToAttrib.SetRepeatFlag(true);
    gfc::schema::CStringType oTo;
    oToAttrib.SetType(&oTo);
    CAttributeCompatibility oCompatibility;
    oCompatibility.init(&oFromAttrib, &oToAttrib, -1);
    EXPECT_EQ(true, L"abc" == oCompatibility.getName());
    EXPECT_EQ(true, oCompatibility.isCompatible());
    //std::wstring sValue = L"('abc','abc,ef','abc')";
    CAttributeValuePtr pValue(new CCompositeAttributeValue);
    pValue->add(CAttributeValuePtr(new CLeafAttributeValue(L"'abc'")));
    pValue->add(CAttributeValuePtr(new CLeafAttributeValue(L"'abc,ef'")));
    pValue->add(CAttributeValuePtr(new CLeafAttributeValue(L"'abc'")));
    oCompatibility.converter()->transform(pValue);
    EXPECT_EQ(true, L"('abc','abc,ef','abc')" == pValue->asString());
}

TEST(TestAttributeCompatibility, Compose_string2)
{
    gfc::schema::CAttribute oFromAttrib;
    oFromAttrib.SetName(L"abc");
    oFromAttrib.SetRepeatFlag(true);
    gfc::schema::CStringType oFrom;
    oFromAttrib.SetType(&oFrom);
    gfc::schema::CAttribute oToAttrib;
    oToAttrib.SetRepeatFlag(true);
    gfc::schema::CIntegerType oTo;
    oToAttrib.SetType(&oTo);
    CAttributeCompatibility oCompatibility;
    oCompatibility.init(&oFromAttrib, &oToAttrib, -1);
    EXPECT_EQ(true, L"abc" == oCompatibility.getName());
    EXPECT_EQ(false, oCompatibility.isCompatible());
    //std::wstring sValue = L"('abc','abc,ef','abc')";
    CAttributeValuePtr pValue(new CCompositeAttributeValue);
    pValue->add(CAttributeValuePtr(new CLeafAttributeValue(L"'abc'")));
    pValue->add(CAttributeValuePtr(new CLeafAttributeValue(L"'abc,ef'")));
    pValue->add(CAttributeValuePtr(new CLeafAttributeValue(L"'abc'")));
    oCompatibility.converter()->transform(pValue);
    EXPECT_EQ(true, L"($,$,$)" == pValue->asString());
}
*/
