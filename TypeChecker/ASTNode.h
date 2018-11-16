//
// Created by Michal Young on 9/12/18.
//

#ifndef REFLEXIVE_ASTNODE_H
#define REFLEXIVE_ASTNODE_H

#include <string>
#include <sstream>
#include <vector>
#include "CodegenContext.h"
#include "EvalContext.h"

namespace AST {
    // Abstract syntax tree.  ASTNode is abstract base class for all other nodes.

    // Json conversion and pretty-printing can pass around a print context object
    // to keep track of indentation, and possibly other things.
    class AST_print_context {
    public:
        int indent_; // Number of spaces to place on left, after each newline
        AST_print_context() : indent_{0} {};
        void indent() { ++indent_; }
        void dedent() { --indent_; }
    };

    class ASTNode {
    public:
        virtual int eval(EvalContext &ctx) = 0;        // Immediate evaluation
        virtual void json(std::ostream& out, AST_print_context& ctx) = 0;  // Json string representation
        virtual std::string return_type() = 0;
        std::string node_name_ = "ASTNode";
        std::string str() {
            std::stringstream ss;
            AST_print_context ctx;
            json(ss, ctx);
            return ss.str();
        }
    protected:
        void json_indent(std::ostream& out, AST_print_context& ctx);
        void json_head(std::string node_kind, std::ostream& out, AST_print_context& ctx);
        void json_close(std::ostream& out, AST_print_context& ctx);
        void json_child(std::string field, ASTNode& child, std::ostream& out, AST_print_context& ctx, char sep=',');
    };

    /* A block is a sequence of statements or expressions.
     * For simplicity we'll just make it a sequence of ASTNode,
     * and leave it to the parser to build valid structures.
     */
    
    class Block : public ASTNode {
    public:
        std::vector<ASTNode*> stmts_;
        std::string node_name_ = "Block";
        
        explicit Block() : stmts_{std::vector<ASTNode*>()} {}
        void append(ASTNode* stmt) { stmts_.push_back(stmt); }
        int eval(EvalContext& ctx) override;
        void json(std::ostream& out, AST_print_context& ctx) override;
        std::string return_type() override;
     };


    /* L_Expr nodes are AST nodes that can be evaluated for location.
     * Most can also be evaluated for value_.  An example of an L_Expr
     * is an identifier, which can appear on the left_ hand or right_ hand
     * side of an assignment.  For example, in x = y, x is evaluated for
     * location and y is evaluated for value_.
     *
     * For now, a location is just a name, because that's what we index
     * the symbol table with.  In a full compiler, locations can be
     * more complex, and typically in code generation we would have
     * LExpr evaluate to an address in a register.
     *
     * LExpr is abstract.  It's only concrete subclass for now is Ident,
     * but in a full OO language we would have LExprs that look like
     * a.b and a[2].
     */
    class LExpr : public ASTNode {
        public:
        std::string node_name_ = "LExpr";
        virtual std::string l_eval(EvalContext& ctx) = 0;
        std::string return_type() override;
       // void json(std::ostream& out, AST_print_context& ctx) override;
    };
    

    /* An assignment has an lvalue (location to be assigned to)
     * and an expression.  We evaluate the expression and place
     * the value_ in the variable.
     */

    class Assign : public ASTNode {
    public:
        LExpr &lexpr_;
        ASTNode &rexpr_;
        std::string node_name_ = "Assign";
        
        Assign(LExpr &lexpr, ASTNode &rexpr) :
           lexpr_{lexpr}, rexpr_{rexpr} {}
        void json(std::ostream& out, AST_print_context& ctx) override;
        int eval(EvalContext& ctx) override;
        std::string return_type() override;
    };

    class If : public ASTNode {
    
    public:
        ASTNode &cond_; // The boolean expression to be evaluated
        Block &truepart_; // Execute this block if the condition is true
        Block &elifpart_; // Node of elif        
        Block &falsepart_; // Execute this block if the condition is false
        std::string node_name_ = "If";
        
        explicit If(ASTNode &cond, Block &truepart, Block &elifpart, Block &falsepart) :
            cond_{cond}, truepart_{truepart}, elifpart_{elifpart},falsepart_{falsepart} { };
        void json(std::ostream& out, AST_print_context& ctx) override;
        int eval(EvalContext& ctx) override;
        std::string return_type() override;

    };
    
    class While : public ASTNode {
        ASTNode &cond_; // The boolean expression to be evaluated
        Block &block_; // Execute this block if the condition is true
    public:
        std::string node_name_ = "While";
        explicit While(ASTNode &cond, Block &block) :
            cond_{cond}, block_{block} { };
        void json(std::ostream& out, AST_print_context& ctx) override;
        int eval(EvalContext& ctx) override;
        std::string return_type() override;

    };

    
 

    /* Identifiers like x and literals like 42 are the
     * leaves of the AST.  A literal can only be evaluated
     * for value_ (the 'eval' method), but an identifier
     * can also be evaluated for location (when we want to
     * store something in it).
     */
    class Ident : public LExpr {
        public:
        std::string text_;
        std::string node_name_ = "Ident";
        
        explicit Ident(std::string txt) : text_{txt} {}
        void json(std::ostream& out, AST_print_context& ctx) override;
        int eval(EvalContext &ctx) override;
        std::string l_eval(EvalContext& ctx) override { return text_; }
        std::string return_type() override;
    };
    
    class Dot: public LExpr {
    public:
        ASTNode &rexpr_;
        ASTNode &ident_;
        std::string node_name_ = "Dot";
        
        explicit Dot(ASTNode &rexpr, ASTNode &ident): rexpr_{rexpr}, ident_{ident} {};
        void json(std::ostream& out, AST_print_context& ctx) override;
        int eval(EvalContext& ctx) override;
        std::string l_eval(EvalContext& ctx) override {return "DOT";}   
        std::string return_type() override; 
        };

    class TypeExtend: public LExpr {
    public:
        LExpr &lexpr_;
        Ident &type_;
        std::string node_name_ = "TypeExtend";
        
        explicit TypeExtend(LExpr &lexpr, Ident &type): lexpr_{lexpr}, type_{type} {};
        void json(std::ostream& out, AST_print_context& ctx) override;
        int eval(EvalContext& ctx) override;
        std::string l_eval(EvalContext& ctx) override {return "TypeExtend";} 
        std::string return_type() override;   
        };

    class IntConst : public ASTNode {
    public:
        int value_;
        std::string node_name_ = "IntConst";
        
        explicit IntConst(int v) : value_{v} {}
        void json(std::ostream& out, AST_print_context& ctx) override;
        int eval(EvalContext &ctx) override { return value_; }
        std::string return_type() override;
    };
    
    class StringConst : public ASTNode {
    public:
        std::string text_;
        std::string node_name_ = "StringConst";
        
        explicit StringConst(std::string t) : text_{t} {}
        void json(std::ostream& out, AST_print_context& ctx) override;
        int eval(EvalContext &ctx) override { return 1; }
        std::string return_type() override;
    };

    // Virtual base class for +, -, *, /, etc
    class BinOp : public ASTNode {
        // each subclass must override the inherited
        // eval() method
    protected:
        std::string opsym;
        BinOp(std::string sym, ASTNode &l, ASTNode &r) :
                opsym{sym}, left_{l}, right_{r} {};
    public:
        ASTNode &left_;
        ASTNode &right_;
        void json(std::ostream& out, AST_print_context& ctx) override;
        std::string return_type() override;
    };
    
    
    class SingleOp : public ASTNode {
        // each subclass must override the inherited
        // eval() method
    protected:
        std::string opsym;
        ASTNode &right_;
        SingleOp(std::string sym, ASTNode &r) :
                opsym{sym}, right_{r} {};
    public:
        void json(std::ostream& out, AST_print_context& ctx) override;
        std::string return_type() override;
    };
    
    class Neg : public SingleOp {
        public:
            std::string node_name_ = "Neg";
            int eval(EvalContext& ctx) override;
            std::string return_type() override;
            Neg(ASTNode &r) :
                    SingleOp(std::string("Neg"), r) {};
    };

    class Plus : public BinOp {
    public:
        std::string node_name_ = "Plus";
        int eval(EvalContext& ctx) override;
        std::string return_type() override;
        Plus(ASTNode &l, ASTNode &r) :
                BinOp(std::string("Plus"),  l, r) {};
    };

    class Minus : public BinOp {
    public:
        std::string node_name_ = "Minus";
        int eval(EvalContext& ctx) override;
        std::string return_type() override;
        Minus(ASTNode &l, ASTNode &r) :
            BinOp(std::string("Minus"),  l, r) {};
    };

    class Times : public BinOp {
    public:
        std::string node_name_ = "Times";
        int eval(EvalContext& ctx) override;
        std::string return_type() override;
        Times(ASTNode &l, ASTNode &r) :
                BinOp(std::string("Times"),  l, r) {};
    };

    class Div : public BinOp {
    public:
        std::string node_name_ = "Div";
        int eval(EvalContext& ctx) override;
        std::string return_type() override;
        Div (ASTNode &l, ASTNode &r) :
                BinOp(std::string("Div"),  l, r) {};
    };
    
    class Large : public BinOp {
    public:
        std::string node_name_ = "Large";
        int eval(EvalContext& ctx) override;
        std::string return_type() override;
        Large (ASTNode &l, ASTNode &r) :
                BinOp(std::string("Large"),  l, r) {};
    };
    
    class Less : public BinOp {
    public:
        std::string node_name_ = "Less";
        int eval(EvalContext& ctx) override;
        std::string return_type() override;
        Less (ASTNode &l, ASTNode &r) :
                BinOp(std::string("Less"),  l, r) {};
    };
    
    class Atleast : public BinOp {
    public:
        std::string node_name_ = "Atleast";
        int eval(EvalContext& ctx) override;
        std::string return_type() override;
        Atleast (ASTNode &l, ASTNode &r) :
                BinOp(std::string("Atleast"),  l, r) {};
    };

    class Atmost : public BinOp {
    public:
        std::string node_name_ = "Atmost";
        int eval(EvalContext& ctx) override;
        std::string return_type() override;
        Atmost (ASTNode &l, ASTNode &r) :
                BinOp(std::string("Atmost"),  l, r) {};
    };


    class Equals : public BinOp {
    public:
        std::string node_name_ = "Equals";
        int eval(EvalContext& ctx) override;
        std::string return_type() override;
        Equals (ASTNode &l, ASTNode &r) :
                BinOp(std::string("Equals"),  l, r) {};
    };

    class And : public BinOp {
    public:
        std::string node_name_ = "And";
        int eval(EvalContext& ctx) override;
        std::string return_type() override;
        And (ASTNode &l, ASTNode &r) :
                BinOp(std::string("And"),  l, r) {};
    };
    
    class Or : public BinOp {
    public:
        std::string node_name_ = "Or";
        int eval(EvalContext& ctx) override;
        std::string return_type() override;
        Or (ASTNode &l, ASTNode &r) :
                BinOp(std::string("Or"),  l, r) {};
    };
    
    class Not : public BinOp {
    public:
        std::string node_name_ = "Not";
        int eval(EvalContext& ctx) override;
        std::string return_type() override;
        Not (ASTNode &l, ASTNode &r) :
                BinOp(std::string("Not"),  l, r) {};
    };


    
    class Class: public ASTNode {
    public:
        Ident &name_;
        ASTNode &inputs_args_;
        Ident &extends_;
        ASTNode &blocks_;
        std::string node_name_ = "Class";
        explicit Class(Ident &name,
                ASTNode &inputs_args, Ident &extends, ASTNode &blocks) :
            name_{name}, inputs_args_{inputs_args}, extends_{extends},
            blocks_{blocks} {};
        void json(std::ostream& out, AST_print_context& ctx) override;
        int eval(EvalContext& ctx) override;
        std::string return_type() override;
        };
    
    
    class Method: public ASTNode {
    public:
        Ident &name_;
        ASTNode &inputs_args_;
        Ident &type_;
        ASTNode &blocks_;
        std::string node_name_ = "Method";
        explicit Method(Ident &name,
                ASTNode &inputs_args, Ident &type, ASTNode &blocks) :
            name_{name}, inputs_args_{inputs_args},type_{type},blocks_{blocks} {};
        void json(std::ostream& out, AST_print_context& ctx) override;
        int eval(EvalContext& ctx) override;
        std::string return_type() override;
        };
        
    class Method_call: public ASTNode {
    public:
        Ident &name_;
        ASTNode &inputs_args_;
        std::string node_name_ = "Method_call";
        explicit Method_call(Ident &name, ASTNode &inputs_args) :name_{name}, inputs_args_{inputs_args} {};
        void json(std::ostream& out, AST_print_context& ctx) override;
        int eval(EvalContext& ctx) override;
        std::string return_type() override;
        };

    
    class Return_opt: public ASTNode {
    public:    
            ASTNode &stmt_;
            std::string node_name_ = "Return_opt";
            explicit Return_opt(ASTNode &stmt): stmt_{stmt} {};
            void json(std::ostream& out, AST_print_context& ctx) override;
            int eval(EvalContext& ctx) override; 
            std::string return_type() override;   
    };
    

    class Argus: public ASTNode {
    public:
        Ident &var_name_;
        Ident &var_type_;
        std::string node_name_ = "Argus";
        explicit Argus(Ident &name, Ident &type):var_name_{name}, var_type_{type} {};
        void json(std::ostream& out, AST_print_context& ctx) override;
        int eval(EvalContext& ctx) override;
        std::string return_type() override;
    };



    class Actuals: public ASTNode {
    public:
            std::vector<ASTNode*> argus_;
            std::string node_name_ = "Actuals";
            explicit Actuals() :argus_{std::vector<ASTNode*>()} {};
            void append(ASTNode* stmt) { argus_.push_back(stmt); }
            void json(std::ostream& out, AST_print_context& ctx) override;
            int eval(EvalContext& ctx) override;
            std::string return_type() override;
        };



    class Classes: public ASTNode {
    public:
            std::vector<ASTNode*> clazzs_;
            std::string node_name_ = "Classes";
            explicit Classes() :clazzs_{std::vector<ASTNode*>()} {};
            void append(ASTNode* clazz) { clazzs_.push_back(clazz); }
            int eval(EvalContext& ctx) override;
            void json(std::ostream& out, AST_print_context& ctx) override;
            std::string return_type() override;
    };
    
    
    
    class Statement: public ASTNode {
    public:
            ASTNode &stmt_;
            std::string node_name_ = "Statement";
            explicit Statement(ASTNode &stmt) :stmt_{stmt} {};
            void json(std::ostream& out, AST_print_context& ctx) override;
            int eval(EvalContext& ctx) override;
            std::string return_type() override;
    };

    class TypeCase: public ASTNode {
        ASTNode &name_;
        Block &block_;
    public:
            std::string node_name_ = "TypeCase";
            explicit TypeCase(ASTNode &name, Block &block): name_{name}, block_{block} {};
            void json(std::ostream& out, AST_print_context& ctx) override;
            int eval(EvalContext& ctx) override;
            std::string return_type() override;
        
    };
    
    class Type_Alternatives: public ASTNode {
        Ident &name_;
        Ident &type_;
        Block &block_;
    public:
            std::string node_name_ = "Type_Alternatives";
            explicit Type_Alternatives(Ident &name, Ident &type, Block &block): name_{name}, type_{type},block_{block} {};
            void json(std::ostream& out, AST_print_context& ctx) override;
            int eval(EvalContext& ctx) override;
            std::string return_type() override;
    };
}
#endif //REFLEXIVE_ASTNODE_H
