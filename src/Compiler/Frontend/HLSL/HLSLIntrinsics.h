/*
 * HLSLIntrinsics.h
 * 
 * This file is part of the XShaderCompiler project (Copyright (c) 2014-2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef XSC_HLSL_INTRINSICS_H
#define XSC_HLSL_INTRINSICS_H


#include "ASTEnums.h"
#include "ShaderVersion.h"
#include "TypeDenoter.h"
#include <map>


namespace Xsc
{


struct HLSLIntrinsicEntry
{
    inline HLSLIntrinsicEntry(Intrinsic intrinsic, int major, int minor) :
        intrinsic       { intrinsic    },
        minShaderModel  { major, minor }
    {
    }

    Intrinsic       intrinsic;
    ShaderVersion   minShaderModel;
};

using HLSLIntrinsicsMap = std::map<std::string, HLSLIntrinsicEntry>;

// Returns the intrinsics map (Intrinsic name -> Intrinsic ID and minimum HLSL shader model).
const HLSLIntrinsicsMap& HLSLIntrinsics();

// Returns a type denoter for the specified intrinsic call and its arguments.
TypeDenoterPtr GetTypeDenoterForHLSLIntrinsicWithArgs(const Intrinsic intrinsic, const std::vector<ExprPtr>& args);


} // /namespace Xsc


#endif



// ================================================================================