/*
 * Generator.h
 * 
 * This file is part of the XShaderCompiler project (Copyright (c) 2014-2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef XSC_GENERATOR_H
#define XSC_GENERATOR_H


#include <Xsc/Xsc.h>
#include "CodeWriter.h"
#include "Visitor.h"
#include "ReportHandler.h"


namespace Xsc
{


// Output code generator base class.
class Generator : protected Visitor
{
    
    public:
        
        Generator(Log* log);

        bool GenerateCode(
            Program& program,
            const ShaderInput& inputDesc,
            const ShaderOutput& outputDesc,
            Log* log = nullptr
        );

    protected:
        
        virtual void GenerateCodePrimary(
            Program& program,
            const ShaderInput& inputDesc,
            const ShaderOutput& outputDesc
        ) = 0;

        void Error(const std::string& msg, const AST* ast = nullptr);
        void ErrorInvalidNumArgs(const std::string& functionName, const AST* ast = nullptr);

        void Warning(const std::string& msg, const AST* ast = nullptr);

        void BeginLn();
        void EndLn();

        void BeginSep();
        void EndSep();

        void Separator();
        
        void WriteScopeOpen(bool compact = false, bool endWithSemicolon = false, bool useBraces = true);
        void WriteScopeClose();
        void WriteScopeContinue();

        bool IsOpenLine() const;
        
        void Write(const std::string& text);
        void WriteLn(const std::string& text);

        void IncIndent();
        void DecIndent();
        
        void PushOptions(const CodeWriter::Options& options);
        void PopOptions();

        void Blank();

        // Returns the current date and time point (can be used in a headline comment).
        std::string TimePoint() const;

        // Returns the AST root node.
        inline Program* GetProgram() const
        {
            return program_;
        }

        // Returns the shader target.
        inline ShaderTarget GetShaderTarget() const
        {
            return shaderTarget_;
        }

        bool IsVertexShader() const;
        bool IsTessControlShader() const;
        bool IsTessEvaluationShader() const;
        bool IsGeometryShader() const;
        bool IsFragmentShader() const;
        bool IsComputeShader() const;

    private:

        CodeWriter      writer_;
        ReportHandler   reportHandler_;

        Program*        program_                = nullptr;

        ShaderTarget    shaderTarget_           = ShaderTarget::VertexShader;

        bool            allowBlanks_            = true;
        bool            allowLineSeparation_    = true;

};


} // /namespace Xsc


#endif



// ================================================================================