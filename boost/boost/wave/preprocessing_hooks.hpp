/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library

    http://www.boost.org/

    Copyright (c) 2001-2007 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#if !defined(DEFAULT_PREPROCESSING_HOOKS_HPP_INCLUDED)
#define DEFAULT_PREPROCESSING_HOOKS_HPP_INCLUDED

#include <boost/wave/wave_config.hpp>
#include <vector>

// this must occur after all of the includes and before any code appears
#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_PREFIX
#endif

///////////////////////////////////////////////////////////////////////////////
namespace boost {
namespace wave {
namespace context_policies {

///////////////////////////////////////////////////////////////////////////////
//  
//  The default_preprocessing_hooks class is a placeholder for all 
//  preprocessing hooks called from inside the preprocessing engine
//
///////////////////////////////////////////////////////////////////////////////
struct default_preprocessing_hooks 
{
    ///////////////////////////////////////////////////////////////////////////
    //  
    //  The function 'expanding_function_like_macro' is called, whenever a 
    //  function-like macro is to be expanded.
    //
    //  The parameter 'macrodef' marks the position, where the macro to expand 
    //  is defined.
    //
    //  The parameter 'formal_args' holds the formal arguments used during the
    //  definition of the macro.
    //
    //  The parameter 'definition' holds the macro definition for the macro to 
    //  trace.
    //
    //  The parameter 'macro_call' marks the position, where this macro invoked.
    //
    //  The parameter 'arguments' holds the macro arguments used during the 
    //  invocation of the macro
    //
    //  The parameters 'seqstart' and 'seqend' point into the input token 
    //  stream allowing to access the whole token sequence comprising the macro
    //  invocation (starting with the opening parenthesis and ending after the
    //  closing one).
    //
    ///////////////////////////////////////////////////////////////////////////

#if BOOST_WAVE_USE_DEPRECIATED_PREPROCESSING_HOOKS != 0
    // old signature
    template <typename TokenT, typename ContainerT>
    void expanding_function_like_macro(
        TokenT const& macrodef, std::vector<TokenT> const& formal_args, 
        ContainerT const& definition,
        TokenT const& macrocall, std::vector<ContainerT> const& arguments) 
    {}
#else
    // new signature
    template <typename ContextT, typename TokenT, typename ContainerT, typename IteratorT>
    void expanding_function_like_macro(ContextT const& ctx,
        TokenT const& macrodef, std::vector<TokenT> const& formal_args, 
        ContainerT const& definition,
        TokenT const& macrocall, std::vector<ContainerT> const& arguments,
        IteratorT const& seqstart, IteratorT const& seqend) 
    {}
#endif

    ///////////////////////////////////////////////////////////////////////////
    //  
    //  The function 'expanding_object_like_macro' is called, whenever a 
    //  object-like macro is to be expanded .
    //
    //  The parameter 'ctx' is a reference to the context object used for 
    //  instantiating the preprocessing iterators by the user.
    //
    //  The parameter 'macro' marks the position, where the macro to expand 
    //  is defined.
    //
    //  The definition 'definition' holds the macro definition for the macro to 
    //  trace.
    //
    //  The parameter 'macrocall' marks the position, where this macro invoked.
    //
    ///////////////////////////////////////////////////////////////////////////
#if BOOST_WAVE_USE_DEPRECIATED_PREPROCESSING_HOOKS != 0
    // old signature
    template <typename TokenT, typename ContainerT>
    void expanding_object_like_macro(TokenT const& macro, 
        ContainerT const& definition, TokenT const& macrocall)
    {}
#else
    // new signature
    template <typename ContextT, typename TokenT, typename ContainerT>
    void expanding_object_like_macro(ContextT const& ctx, TokenT const& macro, 
        ContainerT const& definition, TokenT const& macrocall)
    {}
#endif

    ///////////////////////////////////////////////////////////////////////////
    //  
    //  The function 'expanded_macro' is called, whenever the expansion of a 
    //  macro is finished but before the rescanning process starts.
    //
    //  The parameter 'ctx' is a reference to the context object used for 
    //  instantiating the preprocessing iterators by the user.
    //
    //  The parameter 'result' contains the token sequence generated as the 
    //  result of the macro expansion.
    //
    ///////////////////////////////////////////////////////////////////////////
#if BOOST_WAVE_USE_DEPRECIATED_PREPROCESSING_HOOKS != 0
    // old signature
    template <typename ContainerT>
    void expanded_macro(ContainerT const& result)
    {}
#else
    // new signature
    template <typename ContextT, typename ContainerT>
    void expanded_macro(ContextT const& ctx, ContainerT const& result)
    {}
#endif

    ///////////////////////////////////////////////////////////////////////////
    //  
    //  The function 'rescanned_macro' is called, whenever the rescanning of a 
    //  macro is finished.
    //
    //  The parameter 'ctx' is a reference to the context object used for 
    //  instantiating the preprocessing iterators by the user.
    //
    //  The parameter 'result' contains the token sequence generated as the 
    //  result of the rescanning.
    //
    ///////////////////////////////////////////////////////////////////////////
#if BOOST_WAVE_USE_DEPRECIATED_PREPROCESSING_HOOKS != 0
    // old signature
    template <typename ContainerT>
    void rescanned_macro(ContainerT const& result)
    {}
#else
    // new signature
    template <typename ContextT, typename ContainerT>
    void rescanned_macro(ContextT const& ctx, ContainerT const& result)
    {}
#endif

    ///////////////////////////////////////////////////////////////////////////
    //  
    //  The function 'found_include_directive' is called, whenever a #include
    //  directive was located.
    //
    //  The parameter 'ctx' is a reference to the context object used for 
    //  instantiating the preprocessing iterators by the user.
    //
    //  The parameter 'filename' contains the (expanded) file name found after 
    //  the #include directive. This has the format '<file>', '"file"' or 
    //  'file'.
    //  The formats '<file>' or '"file"' are used for #include directives found 
    //  in the preprocessed token stream, the format 'file' is used for files
    //  specified through the --force_include command line argument.
    //
    //  The parameter 'include_next' is set to true if the found directive was
    //  a #include_next directive and the BOOST_WAVE_SUPPORT_INCLUDE_NEXT
    //  preprocessing constant was defined to something != 0.
    //
    //  The return value defines, whether the found file will be included 
    //  (return true) or will be skipped (return false),
    //
    ///////////////////////////////////////////////////////////////////////////
#if BOOST_WAVE_USE_DEPRECIATED_PREPROCESSING_HOOKS != 0
    // old signature
    void 
    found_include_directive(std::string const& filename, bool include_next) 
    {}
#else
    // new signature
    template <typename ContextT>
    bool 
    found_include_directive(ContextT const& ctx, std::string const& filename, 
        bool include_next) 
    {
        return true;    // ok to include this file
    }
#endif
    
    ///////////////////////////////////////////////////////////////////////////
    //  
    //  The function 'opened_include_file' is called, whenever a file referred 
    //  by an #include directive was successfully located and opened.
    //
    //  The parameter 'ctx' is a reference to the context object used for 
    //  instantiating the preprocessing iterators by the user.
    //
    //  The parameter 'filename' contains the file system path of the 
    //  opened file (this is relative to the directory of the currently 
    //  processed file or a absolute path depending on the paths given as the
    //  include search paths).
    //
    //  The include_depth parameter contains the current include file depth.
    //
    //  The is_system_include parameter denotes, whether the given file was 
    //  found as a result of a #include <...> directive.
    //  
    ///////////////////////////////////////////////////////////////////////////
#if BOOST_WAVE_USE_DEPRECIATED_PREPROCESSING_HOOKS != 0
    // old signature
    void 
    opened_include_file(std::string const& relname, std::string const& absname, 
        std::size_t include_depth, bool is_system_include) 
    {}
#else
    // new signature
    template <typename ContextT>
    void 
    opened_include_file(ContextT const& ctx, std::string const& relname, 
        std::string const& absname, bool is_system_include) 
    {}
#endif
    
    ///////////////////////////////////////////////////////////////////////////
    //  
    //  The function 'returning_from_include_file' is called, whenever an
    //  included file is about to be closed after it's processing is complete.
    //
    //  The parameter 'ctx' is a reference to the context object used for 
    //  instantiating the preprocessing iterators by the user.
    //
    ///////////////////////////////////////////////////////////////////////////
#if BOOST_WAVE_USE_DEPRECIATED_PREPROCESSING_HOOKS != 0
    // old signature
    void
    returning_from_include_file() 
    {}
#else
    // new signature
    template <typename ContextT>
    void
    returning_from_include_file(ContextT const& ctx) 
    {}
#endif

    ///////////////////////////////////////////////////////////////////////////
    //  
    //  The function 'interpret_pragma' is called, whenever a #pragma command 
    //  directive is found which isn't known to the core Wave library, where
    //  command is the value defined as the BOOST_WAVE_PRAGMA_KEYWORD constant
    //  which defaults to "wave".
    //
    //  The parameter 'ctx' is a reference to the context object used for 
    //  instantiating the preprocessing iterators by the user.
    //
    //  The parameter 'pending' may be used to push tokens back into the input 
    //  stream, which are to be used as the replacement text for the whole 
    //  #pragma directive.
    //
    //  The parameter 'option' contains the name of the interpreted pragma.
    //
    //  The parameter 'values' holds the values of the parameter provided to 
    //  the pragma operator.
    //
    //  The parameter 'act_token' contains the actual #pragma token, which may 
    //  be used for error output.
    //
    //  If the return value is 'false', the whole #pragma directive is 
    //  interpreted as unknown and a corresponding error message is issued. A
    //  return value of 'true' signs a successful interpretation of the given 
    //  #pragma.
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename ContextT, typename ContainerT>
    bool 
    interpret_pragma(ContextT const& ctx, ContainerT &pending, 
        typename ContextT::token_type const& option, ContainerT const& values, 
        typename ContextT::token_type const& act_token)
    {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////////
    //
    //  The function 'defined_macro' is called, whenever a macro was defined
    //  successfully.
    //
    //  The parameter 'ctx' is a reference to the context object used for 
    //  instantiating the preprocessing iterators by the user.
    //
    //  The parameter 'name' is a reference to the token holding the macro name.
    //
    //  The parameter 'is_functionlike' is set to true, whenever the newly 
    //  defined macro is defined as a function like macro.
    //
    //  The parameter 'parameters' holds the parameter tokens for the macro
    //  definition. If the macro has no parameters or if it is a object like
    //  macro, then this container is empty.
    //
    //  The parameter 'definition' contains the token sequence given as the
    //  replacement sequence (definition part) of the newly defined macro.
    //
    //  The parameter 'is_predefined' is set to true for all macros predefined 
    //  during the initialization phase of the library.
    //
    ///////////////////////////////////////////////////////////////////////////
#if BOOST_WAVE_USE_DEPRECIATED_PREPROCESSING_HOOKS != 0
    // old signature
    template <typename TokenT, typename ParametersT, typename DefinitionT>
    void
    defined_macro(TokenT const& macro_name, bool is_functionlike, 
        ParametersT const& parameters, DefinitionT const& definition, 
        bool is_predefined)
    {}
#else
    // new signature
    template <
        typename ContextT, typename TokenT, typename ParametersT, 
        typename DefinitionT
    >
    void
    defined_macro(ContextT const& ctx, TokenT const& macro_name, 
        bool is_functionlike, ParametersT const& parameters, 
        DefinitionT const& definition, bool is_predefined)
    {}
#endif

    ///////////////////////////////////////////////////////////////////////////
    //
    //  The function 'undefined_macro' is called, whenever a macro definition
    //  was removed successfully.
    //  
    //  The parameter 'ctx' is a reference to the context object used for 
    //  instantiating the preprocessing iterators by the user.
    //
    //  The parameter 'name' holds the name of the macro, which definition was 
    //  removed.
    //
    ///////////////////////////////////////////////////////////////////////////
#if BOOST_WAVE_USE_DEPRECIATED_PREPROCESSING_HOOKS != 0
    // old signature
    template <typename TokenT>
    void
    undefined_macro(TokenT const& macro_name)
    {}
#else
    // new signature
    template <typename ContextT, typename TokenT>
    void
    undefined_macro(ContextT const& ctx, TokenT const& macro_name)
    {}
#endif
    
    ///////////////////////////////////////////////////////////////////////////
    //
    //  The function 'found_directive' is called, whenever a preprocessor 
    //  directive was encountered, but before the corresponding action is 
    //  executed.
    //
    //  The parameter 'ctx' is a reference to the context object used for 
    //  instantiating the preprocessing iterators by the user.
    //
    //  The parameter 'directive' is a reference to the token holding the 
    //  preprocessing directive.
    //
    ///////////////////////////////////////////////////////////////////////////
#if BOOST_WAVE_USE_DEPRECIATED_PREPROCESSING_HOOKS != 0
    // old signature
    template <typename TokenT>
    void
    found_directive(TokenT const& directive)
    {}
#else
    // new signature
    template <typename ContextT, typename TokenT>
    void
    found_directive(ContextT const& ctx, TokenT const& directive)
    {}
#endif

    ///////////////////////////////////////////////////////////////////////////
    //
    //  The function 'evaluated_conditional_expression' is called, whenever a 
    //  conditional preprocessing expression was evaluated (the expression
    //  given to a #if, #elif, #ifdef or #ifndef directive)
    //
    //  The parameter 'ctx' is a reference to the context object used for 
    //  instantiating the preprocessing iterators by the user.
    //
    //  The parameter 'directive' is a reference to the token holding the 
    //  corresponding preprocessing directive.
    //
    //  The parameter 'expression' holds the non-expanded token sequence
    //  comprising the evaluated expression.
    //
    //  The parameter expression_value contains the result of the evaluation of
    //  the expression in the current preprocessing context.
    //
    //  The return value defines, whether the given expression has to be 
    //  evaluated again, allowing to decide which of the conditional branches
    //  should be expanded. You need to return 'true' from this hook function 
    //  to force the expression to be re-evaluated.
    //
    ///////////////////////////////////////////////////////////////////////////
#if BOOST_WAVE_USE_DEPRECIATED_PREPROCESSING_HOOKS != 0
    // old signature
    template <typename ContainerT>
    void
    evaluated_conditional_expression(ContainerT const& expression, 
        bool expression_value)
    {}
#else
    // new signature
    template <typename ContextT, typename TokenT, typename ContainerT>
    bool
    evaluated_conditional_expression(ContextT const& ctx, 
        TokenT const& directive, ContainerT const& expression, 
        bool expression_value)
    { return false; }         // ok to continue, do not re-evaluate expression
#endif
    
    ///////////////////////////////////////////////////////////////////////////
    //
    //  The function 'skipped_token' is called, whenever a token is about to be
    //  skipped due to a false preprocessor condition (code fragments to be
    //  skipped inside the not evaluated conditional #if/#else/#endif branches).
    //
    //  The parameter 'ctx' is a reference to the context object used for 
    //  instantiating the preprocessing iterators by the user.
    //
    //  The parameter 'token' refers to the token to be skipped.
    //
    ///////////////////////////////////////////////////////////////////////////
#if BOOST_WAVE_USE_DEPRECIATED_PREPROCESSING_HOOKS != 0
    // old signature
    template <typename TokenT>
    void
    skipped_token(TokenT const& token)
    {}
#else
    // new signature
    template <typename ContextT, typename TokenT>
    void
    skipped_token(ContextT const& ctx, TokenT const& token)
    {}
#endif

    ///////////////////////////////////////////////////////////////////////////
    //
    //  The function 'generated_token' will be called by the library whenever a
    //  token is about to be returned from the library.
    //
    //  The parameter 'ctx' is a reference to the context object used for 
    //  instantiating the preprocessing iterators by the user.
    //
    //  The parameter 't' is the token about to be returned from the library.
    //  This function may alter the token, but in this case it must be 
    //  implemented with a corresponding signature: 
    //
    //      TokenT const&
    //      generated_token(ContextT const& ctx, TokenT& t);
    //
    //  which makes it possible to modify the token in place.
    //
    //  The default behavior is to return the token passed as the parameter 
    //  without modification.
    //  
    ///////////////////////////////////////////////////////////////////////////
    template <typename ContextT, typename TokenT>
    TokenT const&
    generated_token(ContextT const& ctx, TokenT const& t)
    { return t; }

    ///////////////////////////////////////////////////////////////////////////
    //
    //  The function 'may_skip_whitespace' will be called by the 
    //  library, whenever it must be tested whether a specific token refers to 
    //  whitespace and this whitespace has to be skipped.
    //
    //  The parameter 'ctx' is a reference to the context object used for 
    //  instantiating the preprocessing iterators by the user.
    //
    //  The 'token' parameter holds a reference to the current token. The policy 
    //  is free to change this token if needed.
    //
    //  The 'skipped_newline' parameter holds a reference to a boolean value 
    //  which should be set to true by the policy function whenever a newline 
    //  is going to be skipped. 
    //
    //  If the return value is true, the given token is skipped and the 
    //  preprocessing continues to the next token. If the return value is 
    //  false, the given token is returned to the calling application. 
    //
    //  ATTENTION!
    //  Caution has to be used, because by returning true the policy function 
    //  is able to force skipping even significant tokens, not only whitespace. 
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename ContextT, typename TokenT>
    bool
    may_skip_whitespace(ContextT const& ctx, TokenT& token, bool& skipped_newline)
    { return false; }

#if BOOST_WAVE_SUPPORT_WARNING_DIRECTIVE != 0
    ///////////////////////////////////////////////////////////////////////////
    //
    //  The function 'found_warning_directive' will be called by the library
    //  whenever a #warning directive is found.
    //
    //  The parameter 'ctx' is a reference to the context object used for 
    //  instantiating the preprocessing iterators by the user.
    //
    //  The parameter 'message' references the argument token sequence of the
    //  encountered #warning directive.
    //
    //  If the return value is false, the library throws a preprocessor 
    //  exception of the type 'warning_directive', if the return value is true
    //  the execution continues as if no #warning directive has been found.
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename ContextT, typename ContainerT>
    bool
    found_warning_directive(ContextT const& ctx, ContainerT const& message)
    { return false; }
#endif

    ///////////////////////////////////////////////////////////////////////////
    //
    //  The function 'found_error_directive' will be called by the library
    //  whenever a #error directive is found.
    //
    //  The parameter 'ctx' is a reference to the context object used for 
    //  instantiating the preprocessing iterators by the user.
    //
    //  The parameter 'message' references the argument token sequence of the
    //  encountered #error directive.
    //
    //  If the return value is false, the library throws a preprocessor 
    //  exception of the type 'error_directive', if the return value is true
    //  the execution continues as if no #error directive has been found.
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename ContextT, typename ContainerT>
    bool
    found_error_directive(ContextT const& ctx, ContainerT const& message)
    { return false; }

    ///////////////////////////////////////////////////////////////////////////
    //
    //  The function 'found_line_directive' will be called by the library
    //  whenever a #line directive is found.
    //
    //  The parameter 'ctx' is a reference to the context object used for 
    //  instantiating the preprocessing iterators by the user.
    //
    //  The parameter 'arguments' references the argument token sequence of the
    //  encountered #line directive.
    //
    //  The parameter 'line' contains the recognized line number from the #line
    //  directive.
    //
    //  The parameter 'filename' references the recognized file name from the 
    //  #line directive (if there was one given).
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename ContextT, typename ContainerT>
    void
    found_line_directive(ContextT const& ctx, ContainerT const& arguments,
        unsigned int line, std::string const& filename)
    {}
    
    ///////////////////////////////////////////////////////////////////////////
    //
    //  The function 'throw_exception' will be called by the library whenever a
    //  preprocessing exception occurs.
    //
    //  The parameter 'ctx' is a reference to the context object used for 
    //  instantiating the preprocessing iterators by the user.
    //
    //  The parameter 'e' is the exception object containing detailed error 
    //  information.
    //
    //  The default behavior is to call the function boost::throw_exception.
    //  
    ///////////////////////////////////////////////////////////////////////////
    template <typename ContextT, typename ExceptionT>
    void
    throw_exception(ContextT const& ctx, ExceptionT const& e)
    {
        boost::throw_exception(e);
    }
};

///////////////////////////////////////////////////////////////////////////////
}   // namespace context_policies
}   // namespace wave
}   // namespace boost

// the suffix header occurs after all of the code
#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // !defined(DEFAULT_PREPROCESSING_HOOKS_HPP_INCLUDED)
