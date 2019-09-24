----------------------------------
--typedef enum asn1p_expr_meta
----------------------------------
AMT_INVALID = 0;
AMT_TYPE = 1;
AMT_TYPEREF = 2;
AMT_VALUE = 3;
AMT_VALUESET = 4;
AMT_OBJECT = 5;
AMT_OBJECTCLASS = 6; 
AMT_OBJECTFIELD = 7;
AMT_EXPR_META_MAX = 8;

----------------------------------
--typedef enum asn1p_expr_type
----------------------------------
A1TC_INVALID = 0x00; --0
A1TC_REFERENCE = 0x01; --1
A1TC_EXPORTVAR = 0x02; --2
A1TC_UNIVERVAL = 0x03; --3
A1TC_BITVECTOR = 0x04; --4
A1TC_OPAQUE = 0x05; --5
A1TC_EXTENSIBLE = 0x06; --6
A1TC_COMPONENTS_OF = 0x07; --7
A1TC_VALUESET = 0x08; --8
A1TC_CLASSDEF = 0x09; --9
A1TC_INSTANCE = 0x0a; --10

ASN_CLASSFIELD_MASK = 0x10; --16
A1TC_CLASSFIELD_TFS = 0x10; --16
A1TC_CLASSFIELD_FTVFS = 0x11; --17
A1TC_CLASSFIELD_VTVFS = 0x12; --18
A1TC_CLASSFIELD_FTVSFS = 0x13; --19
A1TC_CLASSFIELD_VTVSFS = 0x14; --20
A1TC_CLASSFIELD_OFS = 0x15; --21
A1TC_CLASSFIELD_OSFS = 0x16; --22

ASN_CONSTR_MASK = 0x20; --32
ASN_CONSTR_SEQUENCE = 0x20; --32
ASN_CONSTR_CHOICE = 0x21; --33
ASN_CONSTR_SET = 0x22; --34
ASN_CONSTR_SEQUENCE_OF = 0x23; --35
ASN_CONSTR_SET_OF = 0x24; --36
ASN_CONSTR_OPEN_TYPE = 0x25; --37

ASN_BASIC_MASK = 0x40; --64
ASN_TYPE_ANY = 0x40; --64
ASN_BASIC_BOOLEAN = 0x41; --65
ASN_BASIC_NULL = 0x42; --66
ASN_BASIC_INTEGER = 0x43; --67
ASN_BASIC_REAL = 0x44; --68
ASN_BASIC_ENUMERATED = 0x45; --69
ASN_BASIC_BIT_STRING = 0x46; --70
ASN_BASIC_OCTET_STRING = 0x47; --71
ASN_BASIC_OBJECT_IDENTIFIER = 0x48; --72
ASN_BASIC_RELATIVE_OID = 0x49; --73
ASN_BASIC_EXTERNAL = 0x4a; --74
ASN_BASIC_EMBEDDED_PDV = 0x4b; --75
ASN_BASIC_CHARACTER_STRING = 0x4c; --76
ASN_BASIC_UTCTime = 0x4d; --77
ASN_BASIC_GeneralizedTime = 0x4e; --78

ASN_STRING_KM_MASK	= 0x100; --256
ASN_STRING_IA5String = 0x100; --256
ASN_STRING_PrintableString = 0x101; --257
ASN_STRING_VisibleString = 0x102; --258
ASN_STRING_ISO646String = 0x103; --259
ASN_STRING_NumericString = 0x104; --260
ASN_STRING_UniversalString = 0x105; --261
ASN_STRING_BMPString = 0x106; --262

ASN_STRING_NKM_MASK	= 0x200; --512
ASN_STRING_UTF8String = 0x200; --512
ASN_STRING_GeneralString = 0x201; --513
ASN_STRING_GraphicString = 0x202; --514
ASN_STRING_TeletexString = 0x203; --515
ASN_STRING_T61String = 0x204; --516
ASN_STRING_VideotexString = 0x205; --517
ASN_STRING_ObjectDescriptor = 0x206; --518

ASN_STRING_MASK = 0x300; --768

---------------------------------------

function meta_type_to_string(meta_type)
    if meta_type == AMT_INVALID then
        return "AMT_INVALID";
    elseif meta_type == AMT_TYPE then
        return "AMT_TYPE";
    elseif meta_type == AMT_TYPEREF then
        return "AMT_TYPEREF";
    elseif meta_type == AMT_VALUE then
        return "AMT_VALUE";
    elseif meta_type == AMT_VALUESET then
        return "AMT_VALUESET";
    elseif meta_type == AMT_OBJECT then
        return "AMT_OBJECT";
    elseif meta_type == AMT_OBJECTCLASS then
        return "AMT_OBJECTCLASS";
    elseif meta_type == AMT_OBJECTFIELD then
        return "AMT_OBJECTFIELD";
    elseif meta_type == AMT_EXPR_META_MAX then
        return "AMT_EXPR_META_MAX";
    else
        return "<unknown>";
    end
end
---------------
function expr_type_to_string(expr_type)
    if expr_type == A1TC_INVALID then
        return "A1TC_INVALID";
    elseif expr_type == A1TC_REFERENCE then
        return "A1TC_REFERENCE";
    elseif expr_type == A1TC_EXPORTVAR then
        return "A1TC_EXPORTVAR";
    elseif expr_type == A1TC_UNIVERVAL then
        return "A1TC_UNIVERVAL";
    elseif expr_type == A1TC_BITVECTOR then
        return "A1TC_BITVECTOR";
    elseif expr_type == A1TC_OPAQUE then
        return "A1TC_OPAQUE";
    elseif expr_type == A1TC_EXTENSIBLE then
        return "A1TC_EXTENSIBLE";
    elseif expr_type == A1TC_COMPONENTS_OF then
        return "A1TC_COMPONENTS_OF";
    elseif expr_type == A1TC_VALUESET then
        return "A1TC_VALUESET";
    elseif expr_type == A1TC_CLASSDEF then
        return "A1TC_CLASSDEF";
    elseif expr_type == A1TC_INSTANCE then
        return "A1TC_INSTANCE";
    elseif expr_type == A1TC_CLASSFIELD_TFS then
        return "A1TC_CLASSFIELD_TFS";
    elseif expr_type == A1TC_CLASSFIELD_FTVFS then
        return "A1TC_CLASSFIELD_FTVFS";
    elseif expr_type == A1TC_CLASSFIELD_VTVFS then
        return "A1TC_CLASSFIELD_VTVFS";
    elseif expr_type == A1TC_CLASSFIELD_FTVSFS then
        return "A1TC_CLASSFIELD_FTVSFS";
    elseif expr_type == A1TC_CLASSFIELD_VTVSFS then
        return "A1TC_CLASSFIELD_VTVSFS";
    elseif expr_type == A1TC_CLASSFIELD_OFS then
        return "A1TC_CLASSFIELD_OFS";
    elseif expr_type == A1TC_CLASSFIELD_OSFS then
        return "A1TC_CLASSFIELD_OSFS";
    elseif expr_type == ASN_CONSTR_SEQUENCE then
        return "ASN_CONSTR_SEQUENCE";
    elseif expr_type == ASN_CONSTR_CHOICE then
        return "ASN_CONSTR_CHOICE";
    elseif expr_type == ASN_CONSTR_SET then
        return "ASN_CONSTR_SET";
    elseif expr_type == ASN_CONSTR_SEQUENCE_OF then
        return "ASN_CONSTR_SEQUENCE_OF";
    elseif expr_type == ASN_CONSTR_SET_OF then
        return "ASN_CONSTR_SET_OF";
    elseif expr_type == ASN_CONSTR_OPEN_TYPE then
        return "ASN_CONSTR_OPEN_TYPE";
    elseif expr_type == ASN_TYPE_ANY then
        return "ASN_TYPE_ANY";
    elseif expr_type == ASN_BASIC_BOOLEAN then
        return "ASN_BASIC_BOOLEAN";
    elseif expr_type == ASN_BASIC_NULL then
        return "ASN_BASIC_NULL";
    elseif expr_type == ASN_BASIC_INTEGER then
        return "ASN_BASIC_INTEGER";
    elseif expr_type == ASN_BASIC_REAL then
        return "ASN_BASIC_REAL";
    elseif expr_type == ASN_BASIC_ENUMERATED then
        return "ASN_BASIC_ENUMERATED";
    elseif expr_type == ASN_BASIC_BIT_STRING then
        return "ASN_BASIC_BIT_STRING";
    elseif expr_type == ASN_BASIC_OCTET_STRING then
        return "ASN_BASIC_OCTET_STRING";
    elseif expr_type == ASN_BASIC_OBJECT_IDENTIFIER then
        return "ASN_BASIC_OBJECT_IDENTIFIER";
    elseif expr_type == ASN_BASIC_RELATIVE_OID then
        return "ASN_BASIC_RELATIVE_OID";
    elseif expr_type == ASN_BASIC_EXTERNAL then
        return "ASN_BASIC_EXTERNAL";
    elseif expr_type == ASN_BASIC_EMBEDDED_PDV then
        return "ASN_BASIC_EMBEDDED_PDV";
    elseif expr_type == ASN_BASIC_CHARACTER_STRING then
        return "ASN_BASIC_CHARACTER_STRING";
    elseif expr_type == ASN_BASIC_UTCTime then
        return "ASN_BASIC_UTCTime";
    elseif expr_type == ASN_BASIC_GeneralizedTime then
        return "ASN_BASIC_GeneralizedTime";
    elseif expr_type == ASN_STRING_IA5String then
        return "ASN_STRING_IA5String";
    elseif expr_type == ASN_STRING_PrintableString then
        return "ASN_STRING_PrintableString";
    elseif expr_type == ASN_STRING_VisibleString then
        return "ASN_STRING_VisibleString";
    elseif expr_type == ASN_STRING_ISO646String then
        return "ASN_STRING_ISO646String";
    elseif expr_type == ASN_STRING_NumericString then
        return "ASN_STRING_NumericString";
    elseif expr_type == ASN_STRING_UniversalString then
        return "ASN_STRING_UniversalString";
    elseif expr_type == ASN_STRING_BMPString then
        return "ASN_STRING_BMPString";
    elseif expr_type == ASN_STRING_NKM_MASK then
        return "ASN_STRING_NKM_MASK";
    elseif expr_type == ASN_STRING_UTF8String then
        return "ASN_STRING_UTF8String";
    elseif expr_type == ASN_STRING_GeneralString then
        return "ASN_STRING_GeneralString";
    elseif expr_type == ASN_STRING_GraphicString then
        return "ASN_STRING_GraphicString";
    elseif expr_type == ASN_STRING_TeletexString then
        return "ASN_STRING_TeletexString";
    elseif expr_type == ASN_STRING_T61String then
        return "ASN_STRING_T61String";
    elseif expr_type == ASN_STRING_VideotexString then
        return "ASN_STRING_VideotexString";
    elseif expr_type == ASN_STRING_ObjectDescriptor then
        return "ASN_STRING_ObjectDescriptor";
    else
        return "<unknown>"
    end
end

function expr_type_to_c_type(expr_type)
    if expr_type == ASN_BASIC_BOOLEAN then
        return "bool";
    elseif expr_type == ASN_BASIC_INTEGER then
        return "long";
    elseif expr_type == ASN_BASIC_REAL then
        return "double";
    elseif expr_type == ASN_BASIC_BIT_STRING then
        return "BitString";
    elseif expr_type == ASN_BASIC_OCTET_STRING then
        return "OctetString";
    elseif expr_type == ASN_BASIC_UTCTime then
        return "UtcTime";
    elseif expr_type == ASN_STRING_IA5String then
        return "IA5String";
    elseif expr_type == ASN_STRING_UTF8String then
        return "Utf8String";
    end
end

