//
// Created by Michal Young on 9/12/18.
//

#include "ASTNode.h"

namespace AST {
    // Abstract syntax tree.  ASTNode is abstract base class for all other nodes.

    // Each node type needs a str method -- most are in .h file for inlining,
    // a few require more code.


    // Binary operators have an 'eval' method
    int Plus::eval(EvalContext &ctx) { return left_.eval(ctx) + right_.eval(ctx); }

    int Times::eval(EvalContext &ctx) { return left_.eval(ctx) * right_.eval(ctx); }

    int Minus::eval(EvalContext &ctx) { return left_.eval(ctx) - right_.eval(ctx); }

    int Div::eval(EvalContext &ctx) { return left_.eval(ctx) / right_.eval(ctx); }
    
    int Large::eval(EvalContext &ctx) { return left_.eval(ctx) > right_.eval(ctx); }
    
    int Less::eval(EvalContext &ctx) { return left_.eval(ctx) < right_.eval(ctx); }
    
    int Atleast::eval(EvalContext &ctx) { return left_.eval(ctx) >= right_.eval(ctx); }
    
    int Atmost::eval(EvalContext &ctx) { return left_.eval(ctx) <= right_.eval(ctx); }
    
    int Equals::eval(EvalContext &ctx) { return left_.eval(ctx) == right_.eval(ctx); }
    
    int And::eval(EvalContext &ctx) { return left_.eval(ctx) & right_.eval(ctx); }
    
    int Or::eval(EvalContext &ctx) { return left_.eval(ctx) | right_.eval(ctx); }
    
    int Not::eval(EvalContext &ctx) { return left_.eval(ctx) != right_.eval(ctx); }
    
    int Neg::eval(EvalContext &ctx) { return -right_.eval(ctx); }

    // A block is evaluated just by evaluating each statement in the block.
    // We'll return the value_ of the last statement, although it is useless.
    // The value_ of an empty block is zero.
    int Block::eval(EvalContext &ctx) {
        int result = 0;
        for (auto &s: stmts_) {
            result = s->eval(ctx);
        }
        return result;
    }


    // Identifiers live in symtab and default to 0.
    int Ident::eval(EvalContext &ctx) {
        if (ctx.symtab.count(text_) == 1) {
            return ctx.symtab[text_];
        } else {
            return 0;
        }
    }

    // Assignment evaluates its right_ hand side and stores the
    // result into its left_ hand side.  We'll have it return the
    // value_ it produced just for simplicity and debugging, but the
    // value_ is not otherwise used.
    int Assign::eval(EvalContext &ctx) {
        std::string loc = lexpr_.l_eval(ctx);
        int rvalue = rexpr_.eval(ctx);
        ctx.symtab[loc] = rvalue;
        return rvalue;
    }

    // An 'if' statement, in this initial cut, evaluates its condition to an integer
    // and chooses the true (then) part or the false (else) part depending on whether
    // the integer is zero.
    int If::eval(EvalContext &ctx) {
        int cond = cond_.eval(ctx);
        // Might as well use C's ill-considered interpretation of ints as booleans
        if (cond) {
            return truepart_.eval(ctx);
        }
        return falsepart_.eval(ctx);
    }
    
    int While::eval(EvalContext &ctx) {
        int cond = cond_.eval(ctx);
        // Might as well use C's ill-considered interpretation of ints as booleans
        if (cond) {
            return block_.eval(ctx);
        }
        return 0;
    }
    
    
    int Class::eval(EvalContext &ctx){
        return 0;
    }
    
     
    int Method::eval(EvalContext &ctx){
        return 0;
    }
    
    int Method_call::eval(EvalContext &ctx){
        return 0;
    }
    
    int Classes::eval(EvalContext &ctx){
        return 0;
    }
    
    int Argus::eval(EvalContext &ctx){
        return 0;
    }
    
    int Actuals::eval(EvalContext &ctx){
        return 0;
    }
    
    int Statement::eval(EvalContext &ctx){
        return 0;
    }
    
    int Return_opt::eval(EvalContext &ctx){
        return 0;
    }
    
    int Dot::eval(EvalContext &ctx){
        return 0;
    }
    
    int TypeExtend::eval(EvalContext &ctx){
        return 0;
    }
    
    int TypeCase::eval(EvalContext &ctx){
        return 0;
    }
    
    int Type_Alternatives::eval(EvalContext &ctx){
        return 0;
    }

    // JSON representation of all the concrete node types.
    // This might be particularly useful if I want to do some
    // tree manipulation in Python or another language.  We'll
    // do this by emitting into a stream.

    // --- Utility functions used by node-specific json output methods


    /* Indent to a given level */
    void ASTNode::json_indent(std::ostream& out, AST_print_context& ctx) {
        if (ctx.indent_ > 0) {
            out << std::endl;
        }
        for (int i=0; i < ctx.indent_; ++i) {
            out << "    ";
        }
    }

    /* The head element looks like { "kind" : "block", */
    void ASTNode::json_head(std::string node_kind, std::ostream& out, AST_print_context& ctx) {
        json_indent(out, ctx);
        out << "{ \"kind\" : \"" << node_kind << "\"," ;
        ctx.indent();  // one level more for children
        return;
    }

    void ASTNode::json_close(std::ostream& out, AST_print_context& ctx) {
        // json_indent(out, ctx);
        out << "}";
        ctx.dedent();
    }

    void ASTNode::json_child(std::string field, ASTNode& child, std::ostream& out, AST_print_context& ctx, char sep) {
        json_indent(out, ctx);
        out << "\"" << field << "\" : ";
        child.json(out, ctx);
        
        out << sep;
    }


    void Block::json(std::ostream& out, AST_print_context& ctx) {
        json_head("Block", out, ctx);
        // Special case for list of children, but we probably we need to generalize this
        // for other "list of X" nodes, such as parameter lists in Quack.
        out << "\"stmts_\" : [";
        auto sep = "";
        for (ASTNode *stmt: stmts_) {
            out << sep;
            stmt->json(out, ctx);
            sep = ", ";
        }
        out << "]";
        json_close(out, ctx);
    }

    void Assign::json(std::ostream& out, AST_print_context& ctx) {
        json_head("Assign", out, ctx);
        json_child("lexpr_", lexpr_, out, ctx);
        json_child("rexpr_", rexpr_, out, ctx, ' ');
        json_close(out, ctx);
     }

    void If::json(std::ostream& out, AST_print_context& ctx) {
        json_head("If", out, ctx);
        json_child("cond_", cond_, out, ctx);
        json_child("truepart_", truepart_, out, ctx);
        json_child("falsepart_", falsepart_, out, ctx, ' ');
        json_close(out, ctx);
    }
    
    void While::json(std::ostream& out, AST_print_context& ctx) {
        json_head("While", out, ctx);
        json_child("cond_", cond_, out, ctx);
        json_child("block_", block_, out, ctx);
        json_close(out, ctx);
    }
    
    void Ident::json(std::ostream& out, AST_print_context& ctx) {
        json_head("Ident", out, ctx);
        out << "\"text_\" : \"" << text_ << "\"";
        json_close(out, ctx);
    }

    void IntConst::json(std::ostream& out, AST_print_context& ctx) {
        json_head("IntConst", out, ctx);
        out << "\"value_\" : " << value_ ;
        json_close(out, ctx);
    }
    
    void StringConst::json(std::ostream& out, AST_print_context& ctx) {
        json_head("StringConst", out, ctx);
        out << "\"text_\" : " << text_ ;
        json_close(out, ctx);
    }

    void BinOp::json(std::ostream& out, AST_print_context& ctx) {
        json_head(opsym, out, ctx);
        json_child("left_", left_, out, ctx);
        json_child("right_", right_, out, ctx, ' ');
        json_close(out, ctx);
    }
    
    void SingleOp::json(std::ostream& out, AST_print_context& ctx) {
        json_head(opsym, out, ctx);
        json_child("right_", right_, out, ctx);
        json_close(out, ctx);
    }
    
    void Classes::json(std::ostream& out, AST_print_context& ctx) {
            json_head("Classes", out, ctx);
            out << "\"clazzs_\" : [";
            auto sep = "";
            for (ASTNode *clazz: clazzs_) {
                out << sep;
                clazz->json(out, ctx);
                sep = ", ";
            }
            out << "]";
            json_close(out, ctx);
    }
    void Actuals::json(std::ostream& out, AST_print_context& ctx) {
            json_head("Actuals", out, ctx);
             out << "\"argus_\" : [";
                auto sep = "";
                for (ASTNode *argus: argus_) {
                    out << sep;
                    argus->json(out, ctx);
                    sep = ", ";
                }
                out << "]";

            json_close(out, ctx);
    }
    void Argus::json(std::ostream& out, AST_print_context& ctx) {
            json_head("Argus", out, ctx);
            json_child("var_name_", var_name_, out, ctx);
            json_child("var_type_", var_type_, out, ctx);
            json_close(out, ctx);
    }
    
    void Class::json(std::ostream& out, AST_print_context& ctx) {
            json_head("Class", out, ctx);
            json_child("name_", name_, out, ctx);
            json_child("inputs_args_", inputs_args_, out, ctx);
            json_child("extends_", extends_, out, ctx);
            json_child("blocks_", blocks_, out, ctx);
            json_close(out, ctx);
    }
    
    void Method::json(std::ostream& out, AST_print_context& ctx) {
            json_head("Method", out, ctx);
            json_child("name_", name_, out, ctx);
            json_child("inputs_args_", inputs_args_, out, ctx);
            json_child("type_", type_, out, ctx);
            json_child("blocks_", blocks_, out, ctx);
            json_close(out, ctx);
    }
    
    void Method_call::json(std::ostream& out, AST_print_context& ctx) {
            json_head("Method_call", out, ctx);
            json_child("caller_", caller_, out, ctx);
            json_child("name_", name_, out, ctx);
            json_child("inputs_args_", inputs_args_, out, ctx);
            json_close(out, ctx);
    }
    
    void Statement::json(std::ostream& out, AST_print_context& ctx) {
            json_head("Statement", out, ctx);
            json_child("stmt_", stmt_, out, ctx);
            json_close(out, ctx);
    }  
    
    void TypeCase::json(std::ostream& out, AST_print_context& ctx) {
            json_head("TypeCase", out, ctx);
            json_child("name_", name_, out, ctx);
            json_child("block_", block_, out, ctx);
            json_close(out, ctx);
    }    
    
    void Return_opt::json(std::ostream& out, AST_print_context& ctx) {
            json_head("Return_opt", out, ctx);
            json_child("stmt_", stmt_, out, ctx);
            json_close(out, ctx);
    }
    
     void Dot::json(std::ostream& out, AST_print_context& ctx) {
                json_head("Dot", out, ctx);
                json_child("rexpr_", rexpr_, out, ctx);
                json_child("ident_", ident_, out, ctx);
                json_close(out, ctx);
    }
    
    void TypeExtend::json(std::ostream& out, AST_print_context& ctx) {
                json_head("TypeExtend", out, ctx);
                json_child("lrexpr_", lexpr_, out, ctx);
                json_child("type_", type_, out, ctx);
                json_close(out, ctx);
    }
    
    void Type_Alternatives::json(std::ostream& out, AST_print_context& ctx) {
                json_head("Type_Alternatives", out, ctx);
                json_child("name_", name_, out, ctx);
                json_child("type_", type_, out, ctx);
                json_child("block_", block_, out, ctx);
                json_close(out, ctx);
    }
    
    std::string Block::return_type(){
        return "block";
    }
    std::string LExpr::return_type(){
        return "LExpr";
    }
    std::string Assign::return_type(){
        return "Assign";
    }
    std::string If::return_type(){
        return "If";
    }
    std::string While::return_type(){
        return "While";
    }
    std::string Ident::return_type(){
        return "Ident";
    }
    std::string Dot::return_type(){
        return "Dot";
    }
    std::string TypeExtend::return_type(){
        return "TypeExtend";
    }
    std::string IntConst::return_type(){
        return "IntConst";
    }
    std::string StringConst::return_type(){
        return "StringConst";
    }

    std::string BinOp::return_type(){
        return "BinOp";
    }
    std::string SingleOp::return_type(){
        return "SingleOp";
    }
    std::string Neg::return_type(){
        return "Neg";
    }
    std::string Plus::return_type(){
        return "BinOp";
    }
    std::string Minus::return_type(){
        return "BinOp";
    }
    std::string Times::return_type(){
        return "BinOp";
    }
    std::string Div::return_type(){
        return "BinOp";
    }
    std::string Large::return_type(){
        return "Logic_BinOp";
    }
    std::string Less::return_type(){
        return "Logic_BinOp";
    }
    std::string Atleast::return_type(){
        return "Logic_BinOp";
    }
    std::string Atmost::return_type(){
        return "Logic_BinOp";
    }
    std::string Equals::return_type(){
        return "Logic_BinOp";
    }
    std::string And::return_type(){
        return "Logic_BinOp";
    }
    std::string Or::return_type(){
        return "Logic_BinOp";
    }
    std::string Not::return_type(){
        return "Logic_BinOp";
    }
    std::string Class::return_type(){
        return "Class";
    }
    std::string Method::return_type(){
        return "Method";
    }
    std::string Method_call::return_type(){
        return "Method_call";
    }
    std::string Return_opt::return_type(){
        return "Return_opt";
    }
    std::string Argus::return_type(){
        return "Argus";
    }
    std::string Actuals::return_type(){
        return "Actuals";
    }
    std::string Classes::return_type(){
        return "Classes";
    }
    std::string Statement::return_type(){
        return "Statement";
    }
    std::string TypeCase::return_type(){
        return "TypeCase";
    }
    std::string Type_Alternatives::return_type(){
        return "Type_Alternatives";
    }
    std::string Plus::BinOp_name(){
        return "PLUS";
    }
    std::string Minus::BinOp_name(){
        return "MINUS";
    }
    std::string Times::BinOp_name(){
        return "TIMES";
    }
    std::string Div::BinOp_name(){
        return "DIV";
    }
    std::string Large::BinOp_name(){
        return "LARGE";
    }
    std::string Atleast::BinOp_name(){
        return "ATLEAST";
    }
    std::string Less::BinOp_name(){
        return "LESS";
    }
    std::string Atmost::BinOp_name(){
        return "ATMOST";
    }
    std::string Equals::BinOp_name(){
        return "EQUAL";
    }
    std::string And::BinOp_name(){
        return "AND";
    }
    std::string Or::BinOp_name(){
        return "OR";
    }
    std::string Not::BinOp_name(){
        return "NOT";
    }
    
}