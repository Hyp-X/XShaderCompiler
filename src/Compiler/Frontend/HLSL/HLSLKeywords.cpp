/*
 * HLSLKeywords.cpp
 * 
 * This file is part of the XShaderCompiler project (Copyright (c) 2014-2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#include "HLSLKeywords.h"
#include "CiString.h"
#include "Helper.h"
#include <vector>


namespace Xsc
{


template <typename T>
T MapKeywordToType(const std::map<std::string, T>& typeMap, const std::string& keyword, const std::string& typeName)
{
    auto it = typeMap.find(keyword);
    if (it != typeMap.end())
        return it->second;
    else
        throw std::runtime_error("failed to map keyword '" + keyword + "' to " + typeName);
}

/* ----- HLSL Keywords ----- */

static KeywordMapType GenerateKeywordMap()
{
    using T = Token::Types;

    return
    {
        { "true",                    T::BoolLiteral     },
        { "false",                   T::BoolLiteral     },

        { "string",                  T::StringType      },

        { "NULL",                    T::NullLiteral     },

        { "bool",                    T::ScalarType      },
        { "bool1",                   T::ScalarType      },
        { "bool1x1",                 T::ScalarType      },
        { "int",                     T::ScalarType      },
        { "int1",                    T::ScalarType      },
        { "int1x1",                  T::ScalarType      },
        { "uint",                    T::ScalarType      },
        { "uint1",                   T::ScalarType      },
        { "uint1x1",                 T::ScalarType      },
        { "dword",                   T::ScalarType      },
        { "dword1",                  T::ScalarType      },
        { "dword1x1",                T::ScalarType      },
        { "half",                    T::ScalarType      },
        { "half1",                   T::ScalarType      },
        { "half1x1",                 T::ScalarType      },
        { "float",                   T::ScalarType      },
        { "float1",                  T::ScalarType      },
        { "float1x1",                T::ScalarType      },
        { "double",                  T::ScalarType      },
        { "double1",                 T::ScalarType      },
        { "double1x1",               T::ScalarType      },

        { "bool2",                   T::VectorType      },
        { "bool3",                   T::VectorType      },
        { "bool4",                   T::VectorType      },
        { "int2",                    T::VectorType      },
        { "int3",                    T::VectorType      },
        { "int4",                    T::VectorType      },
        { "uint2",                   T::VectorType      },
        { "uint3",                   T::VectorType      },
        { "uint4",                   T::VectorType      },
        { "dword2",                  T::VectorType      },
        { "dword3",                  T::VectorType      },
        { "dword4",                  T::VectorType      },
        { "half2",                   T::VectorType      },
        { "half3",                   T::VectorType      },
        { "half4",                   T::VectorType      },
        { "float2",                  T::VectorType      },
        { "float3",                  T::VectorType      },
        { "float4",                  T::VectorType      },
        { "double2",                 T::VectorType      },
        { "double3",                 T::VectorType      },
        { "double4",                 T::VectorType      },

        { "bool2x2",                 T::MatrixType      },
        { "bool2x3",                 T::MatrixType      },
        { "bool2x4",                 T::MatrixType      },
        { "bool3x2",                 T::MatrixType      },
        { "bool3x3",                 T::MatrixType      },
        { "bool3x4",                 T::MatrixType      },
        { "bool4x2",                 T::MatrixType      },
        { "bool4x3",                 T::MatrixType      },
        { "bool4x4",                 T::MatrixType      },
        { "int2x2",                  T::MatrixType      },
        { "int2x3",                  T::MatrixType      },
        { "int2x4",                  T::MatrixType      },
        { "int3x2",                  T::MatrixType      },
        { "int3x3",                  T::MatrixType      },
        { "int3x4",                  T::MatrixType      },
        { "int4x2",                  T::MatrixType      },
        { "int4x3",                  T::MatrixType      },
        { "int4x4",                  T::MatrixType      },
        { "uint2x2",                 T::MatrixType      },
        { "uint2x3",                 T::MatrixType      },
        { "uint2x4",                 T::MatrixType      },
        { "uint3x2",                 T::MatrixType      },
        { "uint3x3",                 T::MatrixType      },
        { "uint3x4",                 T::MatrixType      },
        { "uint4x2",                 T::MatrixType      },
        { "uint4x3",                 T::MatrixType      },
        { "uint4x4",                 T::MatrixType      },
        { "dword2x2",                T::MatrixType      },
        { "dword2x3",                T::MatrixType      },
        { "dword2x4",                T::MatrixType      },
        { "dword3x2",                T::MatrixType      },
        { "dword3x3",                T::MatrixType      },
        { "dword3x4",                T::MatrixType      },
        { "dword4x2",                T::MatrixType      },
        { "dword4x3",                T::MatrixType      },
        { "dword4x4",                T::MatrixType      },
        { "half2x2",                 T::MatrixType      },
        { "half2x3",                 T::MatrixType      },
        { "half2x4",                 T::MatrixType      },
        { "half3x2",                 T::MatrixType      },
        { "half3x3",                 T::MatrixType      },
        { "half3x4",                 T::MatrixType      },
        { "half4x2",                 T::MatrixType      },
        { "half4x3",                 T::MatrixType      },
        { "half4x4",                 T::MatrixType      },
        { "float2x2",                T::MatrixType      },
        { "float2x3",                T::MatrixType      },
        { "float2x4",                T::MatrixType      },
        { "float3x2",                T::MatrixType      },
        { "float3x3",                T::MatrixType      },
        { "float3x4",                T::MatrixType      },
        { "float4x2",                T::MatrixType      },
        { "float4x3",                T::MatrixType      },
        { "float4x4",                T::MatrixType      },
        { "double2x2",               T::MatrixType      },
        { "double2x3",               T::MatrixType      },
        { "double2x4",               T::MatrixType      },
        { "double3x2",               T::MatrixType      },
        { "double3x3",               T::MatrixType      },
        { "double3x4",               T::MatrixType      },
        { "double4x2",               T::MatrixType      },
        { "double4x3",               T::MatrixType      },
        { "double4x4",               T::MatrixType      },

        { "void",                    T::Void            },

        { "point",                   T::PrimitiveType   },
        { "line",                    T::PrimitiveType   },
        { "lineadj",                 T::PrimitiveType   },
        { "triangle",                T::PrimitiveType   },
        { "triangleadj",             T::PrimitiveType   },

        { "vector",                  T::Vector          },
        { "matrix",                  T::Matrix          },

        { "do",                      T::Do              },
        { "while",                   T::While           },
        { "for",                     T::For             },

        { "if",                      T::If              },
        { "else",                    T::Else            },

        { "switch",                  T::Switch          },
        { "case",                    T::Case            },
        { "default",                 T::Default         },

        { "typedef",                 T::Typedef         },
        { "struct",                  T::Struct          },
        { "register",                T::Register        },
        { "packoffset",              T::PackOffset      },

        { "sampler",                 T::Sampler         },
        { "sampler1D",               T::Sampler         },
        { "sampler2D",               T::Sampler         },
        { "sampler3D",               T::Sampler         },
        { "samplerCUBE",             T::Sampler         },

        { "sampler_state",           T::SamplerState    },
        { "SamplerState",            T::SamplerState    }, // since D3D10+
        { "SamplerComparisonState",  T::SamplerState    }, // since D3D10+

        { "texture",                 T::Buffer          },
        { "Texture1D",               T::Buffer          },
        { "Texture1DArray",          T::Buffer          },
        { "Texture2D",               T::Buffer          },
        { "Texture2DArray",          T::Buffer          },
        { "Texture3D",               T::Buffer          },
        { "TextureCube",             T::Buffer          },
        { "TextureCubeArray",        T::Buffer          },
        { "Texture2DMS",             T::Buffer          },
        { "Texture2DMSArray",        T::Buffer          },
        { "RWTexture1D",             T::Buffer          },
        { "RWTexture1DArray",        T::Buffer          },
        { "RWTexture2D",             T::Buffer          },
        { "RWTexture2DArray",        T::Buffer          },
        { "RWTexture3D",             T::Buffer          },

        { "Buffer",                  T::Buffer          },
        { "StructuredBuffer",        T::Buffer          },
        { "ByteAddressBuffer",       T::Buffer          },
        { "RWBuffer",                T::Buffer          },
        { "RWByteAddressBuffer",     T::Buffer          },
        { "RWStructuredBuffer",      T::Buffer          },
        { "AppendStructuredBuffer",  T::Buffer          },
        { "ConsumeStructuredBuffer", T::Buffer          },

        { "InputPatch",              T::Buffer          },
        { "OutputPatch",             T::Buffer          },

        { "PointStream",             T::Buffer          },
        { "LineStream",              T::Buffer          },
        { "TriangleStream",          T::Buffer          },

        { "cbuffer",                 T::UniformBuffer   },
        { "tbuffer",                 T::UniformBuffer   },

        { "break",                   T::CtrlTransfer    },
        { "continue",                T::CtrlTransfer    },
        { "discard",                 T::CtrlTransfer    },

        { "return",                  T::Return          },

        { "uniform",                 T::InputModifier   },
        { "in",                      T::InputModifier   },
        { "out",                     T::InputModifier   },
        { "inout",                   T::InputModifier   },

        { "linear",                  T::InterpModifier  },
        { "centroid",                T::InterpModifier  },
        { "nointerpolation",         T::InterpModifier  },
        { "noperspective",           T::InterpModifier  },
        { "sample",                  T::InterpModifier  },

        { "const",                   T::TypeModifier    },
        { "row_major",               T::TypeModifier    },
        { "column_major",            T::TypeModifier    },
        { "snorm",                   T::TypeModifier    },
        { "unorm",                   T::TypeModifier    },

        { "extern",                  T::StorageClass    },
        { "precise",                 T::StorageClass    },
        { "shared",                  T::StorageClass    },
        { "groupshared",             T::StorageClass    },
        { "static",                  T::StorageClass    },
        { "volatile",                T::StorageClass    },

        { "inline",                  T::Inline          },

        { "technique",               T::Technique       },
        { "pass",                    T::Pass            },
        { "compile",                 T::Compile         },

        { "auto",                    T::Reserved        },
        { "catch",                   T::Reserved        },
        { "char",                    T::Reserved        },
        { "const_cast",              T::Reserved        },
        { "delete",                  T::Reserved        },
        { "dynamic_cast",            T::Reserved        },
        { "enum",                    T::Reserved        },
        { "explicit",                T::Reserved        },
        { "friend",                  T::Reserved        },
        { "goto",                    T::Reserved        },
        { "long",                    T::Reserved        },
        { "mutable",                 T::Reserved        },
        { "new",                     T::Reserved        },
        { "operator",                T::Reserved        },
        { "private",                 T::Reserved        },
        { "protected",               T::Reserved        },
        { "public",                  T::Reserved        },
        { "reinterpret_cast",        T::Reserved        },
        { "short",                   T::Reserved        },
        { "signed",                  T::Reserved        },
        { "sizeof",                  T::Reserved        },
        { "static_cast",             T::Reserved        },
        { "template",                T::Reserved        },
        { "this",                    T::Reserved        },
        { "throw",                   T::Reserved        },
        { "try",                     T::Reserved        },
        { "typename",                T::Reserved        },
        { "union",                   T::Reserved        },
        { "unsigned",                T::Reserved        },
        { "using",                   T::Reserved        },
        { "virtual",                 T::Reserved        },

        { "interface",               T::Unsupported     },
        { "class",                   T::Unsupported     },
    };
}

const KeywordMapType& HLSLKeywords()
{
    static const auto keywordMap = GenerateKeywordMap();
    return keywordMap;
}


/* ----- DataType Mapping ----- */

static std::map<std::string, DataType> GenerateDataTypeMap()
{
    using T = DataType;

    return
    {
        { "string",    T::String    },

        { "bool",      T::Bool      },
        { "bool1",     T::Bool      },
        { "bool1x1",   T::Bool      },
        { "int",       T::Int       },
        { "int1",      T::Int       },
        { "int1x1",    T::Int       },
        { "uint",      T::UInt      },
        { "uint1",     T::UInt      },
        { "uint1x1",   T::UInt      },
        { "dword",     T::UInt      },
        { "dword1",    T::UInt      },
        { "dword1x1",  T::UInt      },
        { "half",      T::Half      },
        { "half1",     T::Half      },
        { "half1x1",   T::Half      },
        { "float",     T::Float     },
        { "float1",    T::Float     },
        { "float1x1",  T::Float     },
        { "double",    T::Double    },
        { "double1",   T::Double    },
        { "double1x1", T::Double    },

        { "bool2",     T::Bool2     },
        { "bool3",     T::Bool3     },
        { "bool4",     T::Bool4     },
        { "int2",      T::Int2      },
        { "int3",      T::Int3      },
        { "int4",      T::Int4      },
        { "uint2",     T::UInt2     },
        { "uint3",     T::UInt3     },
        { "uint4",     T::UInt4     },
        { "dword2",    T::UInt2     },
        { "dword3",    T::UInt3     },
        { "dword4",    T::UInt4     },
        { "half2",     T::Half2     },
        { "half3",     T::Half3     },
        { "half4",     T::Half4     },
        { "float2",    T::Float2    },
        { "float3",    T::Float3    },
        { "float4",    T::Float4    },
        { "double2",   T::Double2   },
        { "double3",   T::Double3   },
        { "double4",   T::Double4   },

        { "bool2x2",   T::Bool2x2   },
        { "bool2x3",   T::Bool2x3   },
        { "bool2x4",   T::Bool2x4   },
        { "bool3x2",   T::Bool3x2   },
        { "bool3x3",   T::Bool3x3   },
        { "bool3x4",   T::Bool3x4   },
        { "bool4x2",   T::Bool4x2   },
        { "bool4x3",   T::Bool4x3   },
        { "bool4x4",   T::Bool4x4   },
        { "int2x2",    T::Int2x2    },
        { "int2x3",    T::Int2x3    },
        { "int2x4",    T::Int2x4    },
        { "int3x2",    T::Int3x2    },
        { "int3x3",    T::Int3x3    },
        { "int3x4",    T::Int3x4    },
        { "int4x2",    T::Int4x2    },
        { "int4x3",    T::Int4x3    },
        { "int4x4",    T::Int4x4    },
        { "uint2x2",   T::UInt2x2   },
        { "uint2x3",   T::UInt2x3   },
        { "uint2x4",   T::UInt2x4   },
        { "uint3x2",   T::UInt3x2   },
        { "uint3x3",   T::UInt3x3   },
        { "uint3x4",   T::UInt3x4   },
        { "uint4x2",   T::UInt4x2   },
        { "uint4x3",   T::UInt4x3   },
        { "uint4x4",   T::UInt4x4   },
        { "dword2x2",  T::UInt2x2   },
        { "dword2x3",  T::UInt2x3   },
        { "dword2x4",  T::UInt2x4   },
        { "dword3x2",  T::UInt3x2   },
        { "dword3x3",  T::UInt3x3   },
        { "dword3x4",  T::UInt3x4   },
        { "dword4x2",  T::UInt4x2   },
        { "dword4x3",  T::UInt4x3   },
        { "dword4x4",  T::UInt4x4   },
        { "half2x2",   T::Half2x2   },
        { "half2x3",   T::Half2x3   },
        { "half2x4",   T::Half2x4   },
        { "half3x2",   T::Half3x2   },
        { "half3x3",   T::Half3x3   },
        { "half3x4",   T::Half3x4   },
        { "half4x2",   T::Half4x2   },
        { "half4x3",   T::Half4x3   },
        { "half4x4",   T::Half4x4   },
        { "float2x2",  T::Float2x2  },
        { "float2x3",  T::Float2x3  },
        { "float2x4",  T::Float2x4  },
        { "float3x2",  T::Float3x2  },
        { "float3x3",  T::Float3x3  },
        { "float3x4",  T::Float3x4  },
        { "float4x2",  T::Float4x2  },
        { "float4x3",  T::Float4x3  },
        { "float4x4",  T::Float4x4  },
        { "double2x2", T::Double2x2 },
        { "double2x3", T::Double2x3 },
        { "double2x4", T::Double2x4 },
        { "double3x2", T::Double3x2 },
        { "double3x3", T::Double3x3 },
        { "double3x4", T::Double3x4 },
        { "double4x2", T::Double4x2 },
        { "double4x3", T::Double4x3 },
        { "double4x4", T::Double4x4 },
    };
}

DataType HLSLKeywordToDataType(const std::string& keyword)
{
    static const auto typeMap = GenerateDataTypeMap();
    return MapKeywordToType(typeMap, keyword, "data type");
}


/* ----- PrimitiveType Mapping ----- */

static std::map<std::string, PrimitiveType> GeneratePrimitiveTypeMap()
{
    using T = PrimitiveType;

    return
    {
        { "point",       T::Point       },
        { "line",        T::Line        },
        { "lineadj",     T::LineAdj     },
        { "triangle",    T::Triangle    },
        { "triangleadj", T::TriangleAdj },
    };
}

PrimitiveType HLSLKeywordToPrimitiveType(const std::string& keyword)
{
    static const auto typeMap = GeneratePrimitiveTypeMap();
    return MapKeywordToType(typeMap, keyword, "primitive type");
}


/* ----- StorageClass Mapping ----- */

static std::map<std::string, StorageClass> GenerateStorageClassMap()
{
    using T = StorageClass;

    return
    {
        { "extern",          T::Extern          },
        { "precise",         T::Precise         },
        { "shared",          T::Shared          },
        { "groupshared",     T::GroupShared     },
        { "static",          T::Static          },
        { "volatile",        T::Volatile        },
    };
}

StorageClass HLSLKeywordToStorageClass(const std::string& keyword)
{
    static const auto typeMap = GenerateStorageClassMap();
    return MapKeywordToType(typeMap, keyword, "storage class");
}


/* ----- InterpModifier Mapping ----- */

static std::map<std::string, InterpModifier> GenerateInterpModifierMap()
{
    using T = InterpModifier;

    return
    {
        { "linear",          T::Linear          },
        { "centroid",        T::Centroid        },
        { "nointerpolation", T::NoInterpolation },
        { "noperspective",   T::NoPerspective   },
        { "sample",          T::Sample          },
    };
}

InterpModifier HLSLKeywordToInterpModifier(const std::string& keyword)
{
    static const auto typeMap = GenerateInterpModifierMap();
    return MapKeywordToType(typeMap, keyword, "interpolation modifier");
}


/* ----- TypeModifier Mapping ----- */

static std::map<std::string, TypeModifier> GenerateTypeModifierMap()
{
    using T = TypeModifier;

    return
    {
        { "const",        T::Const       },
        { "row_major",    T::RowMajor    },
        { "column_major", T::ColumnMajor },

        { "snorm",        T::SNorm       },
        { "unorm",        T::UNorm       },
    };
}

TypeModifier HLSLKeywordToTypeModifier(const std::string& keyword)
{
    static const auto typeMap = GenerateTypeModifierMap();
    return MapKeywordToType(typeMap, keyword, "type modifier");
}


/* ----- BufferType Mapping ----- */

static std::map<std::string, UniformBufferType> GenerateUniformBufferTypeMap()
{
    using T = UniformBufferType;

    return
    {
        { "cbuffer", T::ConstantBuffer },
        { "tbuffer", T::TextureBuffer  },
    };
}

UniformBufferType HLSLKeywordToUniformBufferType(const std::string& keyword)
{
    static const auto typeMap = GenerateUniformBufferTypeMap();
    return MapKeywordToType(typeMap, keyword, "buffer type");
}


/* ----- BufferType Mapping ----- */

static std::map<std::string, BufferType> GenerateBufferTypeMap()
{
    using T = BufferType;

    return
    {
        { "Buffer",                  T::Buffer                  },
        { "StructuredBuffer",        T::StructuredBuffer        },
        { "ByteAddressBuffer",       T::ByteAddressBuffer       },

        { "RWBuffer",                T::RWBuffer                },
        { "RWStructuredBuffer",      T::RWStructuredBuffer      },
        { "RWByteAddressBuffer",     T::RWByteAddressBuffer     },
        { "AppendStructuredBuffer",  T::AppendStructuredBuffer  },
        { "ConsumeStructuredBuffer", T::ConsumeStructuredBuffer },

        { "RWTexture1D",             T::RWTexture1D             },
        { "RWTexture1DArray",        T::RWTexture1DArray        },
        { "RWTexture2D",             T::RWTexture2D             },
        { "RWTexture2DArray",        T::RWTexture2DArray        },
        { "RWTexture3D",             T::RWTexture3D             },

        { "Texture1D",               T::Texture1D               },
        { "Texture1DArray",          T::Texture1DArray          },
        { "Texture2D",               T::Texture2D               },
        { "Texture2DArray",          T::Texture2DArray          },
        { "Texture3D",               T::Texture3D               },
        { "TextureCube",             T::TextureCube             },
        { "TextureCubeArray",        T::TextureCubeArray        },
        { "Texture2DMS",             T::Texture2DMS             },
        { "Texture2DMSArray",        T::Texture2DMSArray        },

        { "texture",                 T::GenericTexture          },

        { "InputPatch",              T::InputPatch              },
        { "OutputPatch",             T::OutputPatch             },

        { "PointStream",             T::PointStream             },
        { "LineStream",              T::LineStream              },
        { "TriangleStream",          T::TriangleStream          },
    };
}

BufferType HLSLKeywordToBufferType(const std::string& keyword)
{
    static const auto typeMap = GenerateBufferTypeMap();
    return MapKeywordToType(typeMap, keyword, "buffer type");
}


/* ----- SamplerType Mapping ----- */

static std::map<std::string, SamplerType> GenerateSamplerTypeMap()
{
    using T = SamplerType;

    return
    {
        { "sampler1D",              T::Sampler1D              },
        { "sampler2D",              T::Sampler2D              },
        { "sampler3D",              T::Sampler3D              },
        { "samplerCUBE",            T::SamplerCube            },
        { "sampler",                T::SamplerState           },
        { "sampler_state",          T::SamplerState           },
        { "SamplerState",           T::SamplerState           },
        { "SamplerComparisonState", T::SamplerComparisonState },
    };
}

SamplerType HLSLKeywordToSamplerType(const std::string& keyword)
{
    static const auto typeMap = GenerateSamplerTypeMap();
    return MapKeywordToType(typeMap, keyword, "sampler type");
}


/* ----- AttributeType Mapping ----- */

static std::map<std::string, AttributeType> GenerateAttributeTypeMap()
{
    using T = AttributeType;

    return
    {
        { "branch",                    T::Branch                    },
        { "call",                      T::Call                      },
        { "flatten",                   T::Flatten                   },
        { "ifAll",                     T::IfAll                     },
        { "ifAny",                     T::IfAny                     },
        { "isolate",                   T::Isolate                   },
        { "loop",                      T::Loop                      },
        { "maxexports",                T::MaxExports                },
        { "maxInstructionCount",       T::MaxInstructionCount       },
        { "maxtempreg",                T::MaxTempReg                },
        { "noExpressionOptimizations", T::NoExpressionOptimizations },
        { "predicate",                 T::Predicate                 },
        { "predicateBlock",            T::PredicateBlock            },
        { "reduceTempRegUsage",        T::ReduceTempRegUsage        },
        { "removeUnusedInputs",        T::RemoveUnusedInputs        },
        { "sampreg",                   T::SampReg                   },
        { "unroll",                    T::Unroll                    },
        { "unused",                    T::Unused                    },
        { "xps",                       T::Xps                       },

        { "domain",                    T::Domain                    },
        { "earlydepthstencil",         T::EarlyDepthStencil         },
        { "instance",                  T::Instance                  },
        { "maxtessfactor",             T::MaxTessFactor             },
        { "maxvertexcount",            T::MaxVertexCount            },
        { "numthreads",                T::NumThreads                },
        { "outputcontrolpoints",       T::OutputControlPoints       },
        { "outputtopology",            T::OutputTopology            },
        { "partitioning",              T::Partitioning              },
        { "patchsize",                 T::PatchSize                 },
        { "patchconstantfunc",         T::PatchConstantFunc         },
    };
}

AttributeType HLSLKeywordToAttributeType(const std::string& keyword)
{
    static const auto typeMap = GenerateAttributeTypeMap();
    auto it = typeMap.find(keyword);
    return (it != typeMap.end() ? it->second : AttributeType::Undefined);
}


/* ----- AttributeValue Mapping ----- */

static std::map<std::string, AttributeValue> GenerateAttributeValueMap()
{
    using T = AttributeValue;

    return
    {
        { "tri",             T::DomainTri                  },
        { "quad",            T::DomainQuad                 },
        { "isoline",         T::DomainIsoline              },

        { "point",           T::OutputTopologyPoint        },
        { "line",            T::OutputTopologyLine         },
        { "triangle_cw",     T::OutputTopologyTriangleCW   },
        { "triangle_ccw",    T::OutputTopologyTriangleCCW  },

        { "integer",         T::PartitioningInteger        },
        { "pow2",            T::PartitioningPow2           },
        { "fractional_even", T::PartitioningFractionalEven },
        { "fractional_odd",  T::PartitioningFractionalOdd  },
    };
}

AttributeValue HLSLKeywordToAttributeValue(const std::string& keyword)
{
    static const auto typeMap = GenerateAttributeValueMap();
    auto it = typeMap.find(keyword);
    return (it != typeMap.end() ? it->second : AttributeValue::Undefined);
}


/* ----- Semantic Mapping ----- */

struct HLSLSemanticDescriptor
{
    inline HLSLSemanticDescriptor(const Semantic semantic, bool hasIndex = false) :
        semantic{ semantic },
        hasIndex{ hasIndex }
    {
    }

    Semantic    semantic;
    bool        hasIndex    = false;
};

using HLSLSemanticMap = std::vector<std::pair<CiString, HLSLSemanticDescriptor>>;

static IndexedSemantic HLSLKeywordToSemanticWithMap(const CiString& ident, const HLSLSemanticMap& semanticMap)
{
    for (const auto& s : semanticMap)
    {
        if (s.second.hasIndex)
        {
            /* Does the identifier equal the semantic name without the index? */
            if (ident.size() >= s.first.size() && ident.compare(0, s.first.size(), s.first) == 0)
            {
                /* Is identifier longer than semantic name? */
                if (ident.size() > s.first.size())
                {
                    /* Return semantic with index */
                    auto index = FromString<int>(ident.substr(s.first.size()).c_str());
                    return { s.second.semantic, index };
                }
                return s.second.semantic;
            }
        }
        else if (ident == s.first)
            return s.second.semantic;
    }
    return IndexedSemantic(std::string(ident.begin(), ident.end()));
}

static IndexedSemantic HLSLKeywordToSemanticD3D9(const CiString& ident)
{
    using T = Semantic;

    static const HLSLSemanticMap semanticMap
    {
        { "COLOR",    { T::Target,         true } },
        { "DEPTH",    { T::Depth,          true } },
        { "POSITION", { T::VertexPosition, true } },
        { "VFACE",    { T::IsFrontFace          } },
        { "VPOS",     { T::Position             } },
        //TODO: continue this list ...
    };

    /* Has identifier at the the length of the shortest semantic? */
    if (ident.size() >= 4)
        return HLSLKeywordToSemanticWithMap(ident, semanticMap);
    else
        return IndexedSemantic(std::string(ident.begin(), ident.end()));
}

static IndexedSemantic HLSLKeywordToSemanticD3D10(const CiString& ident)
{
    using T = Semantic;

    static const HLSLSemanticMap semanticMap
    {
        { "SV_ClipDistance",           { T::ClipDistance,          true } },
        { "SV_CullDistance",           { T::CullDistance,          true } },
        { "SV_Coverage",               { T::Coverage                    } },
        { "SV_Depth",                  { T::Depth                       } },
        { "SV_DepthGreaterEqual",      { T::DepthGreaterEqual           } },
        { "SV_DepthLessEqual",         { T::DepthLessEqual              } },
        { "SV_DispatchThreadID",       { T::DispatchThreadID            } },
        { "SV_DomainLocation",         { T::DomainLocation              } },
        { "SV_GroupID",                { T::GroupID                     } },
        { "SV_GroupIndex",             { T::GroupIndex                  } },
        { "SV_GroupThreadID",          { T::GroupThreadID               } },
        { "SV_GSInstanceID",           { T::GSInstanceID                } },
        { "SV_InnerCoverage",          { T::InnerCoverage               } },
        { "SV_InsideTessFactor",       { T::InsideTessFactor            } },
        { "SV_InstanceID",             { T::InstanceID                  } },
        { "SV_IsFrontFace",            { T::IsFrontFace                 } },
        { "SV_OutputControlPointID",   { T::OutputControlPointID        } },
        { "SV_Position",               { T::Position                    } },
        { "SV_PrimitiveID",            { T::PrimitiveID                 } },
        { "SV_RenderTargetArrayIndex", { T::RenderTargetArrayIndex      } },
        { "SV_SampleIndex",            { T::SampleIndex                 } },
        { "SV_StencilRef",             { T::StencilRef                  } },
        { "SV_Target",                 { T::Target,                true } },
        { "SV_TessFactor",             { T::TessFactor                  } },
        { "SV_VertexID",               { T::VertexID                    } },
      //{ "SV_Position",               { T::VertexPosition              } }, // Special case (SV_Position is overloaded)
        { "SV_ViewportArrayIndex",     { T::ViewportArrayIndex          } },
    };

    /* Has identifier at the the length of the shortest semantic? */
    if (ident.size() >= 4 && ident.compare(0, 3, "SV_") == 0)
    {
        auto semantic = HLSLKeywordToSemanticWithMap(ident, semanticMap);
        if (semantic.IsUserDefined())
            throw std::runtime_error("invalid system value semantic \"" + std::string(ident.begin(), ident.end()) + "\"");
        return semantic;
    }
    else
        return IndexedSemantic(std::string(ident.begin(), ident.end()));
}

IndexedSemantic HLSLKeywordToSemantic(const std::string& ident, bool useD3D10Semantics)
{
    if (useD3D10Semantics)
        return HLSLKeywordToSemanticD3D10(ToCiString(ident));
    else
        return HLSLKeywordToSemanticD3D9(ToCiString(ident));
}


} // /namespace Xsc



// ================================================================================