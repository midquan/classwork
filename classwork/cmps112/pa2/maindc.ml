(* $Id: maindc.ml,v 1.5 2017-04-07 13:24:41-07 - - $ 
NAME
	maindc.ml - 

SYNOPSIS
	maindc.ml
	
DESCRIPTION
	This file is used to scan input and create the Bigint which is used for the dc. 

PARTNERS
	Daniel Lung dlung@ucsc.edu
	Michael Quan midquan@ucsc.edu
*)
include Scanner
include Bigint

open Bigint
open Printf
open Scanner

type stack_t = Bigint.bigint Stack.t
let push = Stack.push
let pop = Stack.pop

let aget = Array.get
let aset = Array.set
let amake = Array.make

let ord thechar = int_of_char thechar
type binop_t = bigint -> bigint -> bigint

let rec print_number number = 
    let big = string_of_bigint number in
    if (String.length big) > 69
		then ( printf "%s\\\n%!" (String.sub big 0 69);
           print_number (bigint_of_string (String.sub big 69 
		   ((String.length big) - 69) )))
	else printf "%s\n%!" big
	
let print_stackempty () = printf "stack empty\n%!"


let symbol_table = amake 256 (false, Bigint.zero)

(* store values into array, based off of registers.ml starter code *)
let do_store sym value = 
	aset symbol_table sym (true, value)

(* load values from array , based off of registers.ml starter code *)
let do_load sym thestack = 
	let entry = aget symbol_table sym in match entry with
		| false, _ -> printf "register '%d' is empty\n%!" sym
		| true, value -> push value thestack

		
(* modified executereg to enable l and s commands *)
let executereg (thestack: stack_t) (oper: char) (reg: int) =
    try match oper with
        | 'l' -> do_load reg thestack
        | 's' -> do_store reg (pop thestack)
        | _   -> printf "0%o 0%o is unimplemented\n%!" (ord oper) reg
    with Stack.Empty -> print_stackempty()


let executebinop (thestack: stack_t) (oper: binop_t) =
    try let right = pop thestack
        in  try let left = pop thestack
                in  push (oper left right) thestack
            with Stack.Empty -> (print_stackempty ();
                                 push right thestack)
    with Stack.Empty -> print_stackempty ()

let execute (thestack: stack_t) (oper: char) =
    try match oper with
        | '+'  -> executebinop thestack Bigint.add
        | '-'  -> executebinop thestack Bigint.sub
        | '*'  -> executebinop thestack Bigint.mul
        | '/'  -> executebinop thestack Bigint.div
        | '%'  -> executebinop thestack Bigint.rem
        | '^'  -> executebinop thestack Bigint.pow
        | 'c'  -> Stack.clear thestack
        | 'd'  -> push (Stack.top thestack) thestack
        | 'f'  -> Stack.iter print_number thestack
        | 'l'  -> failwith "operator l scanned with no register"
        | 'p'  -> print_number (Stack.top thestack)
        | 'q'  -> raise End_of_file
        | 's'  -> failwith "operator s scanned with no register"
        | '\n' -> ()
        | ' '  -> ()
        | _    -> printf "0%o is unimplemented\n%!" (ord oper)
    with Stack.Empty -> print_stackempty()

let toploop (thestack: stack_t) inputchannel =
    let scanbuf = Lexing.from_channel inputchannel in
    let rec toploop () = 
        try  let nexttoken = Scanner.scanner scanbuf
             in  (match nexttoken with
                 | Number number       -> push number thestack
                 | Regoper (oper, reg) -> executereg thestack oper reg
                 | Operator oper       -> execute thestack oper
                 );
             toploop ()
        with End_of_file -> printf "%!";
    in  toploop ()

let readfiles () =
    let thestack : bigint Stack.t = Stack.create ()
    in  ((if Array.length Sys.argv > 1 
         then try  let thefile = open_in Sys.argv.(1)
                   in  toploop thestack thefile
              with Sys_error message -> (
                   printf "%s: %s\n%!" Sys.argv.(0) message;
                   exit 1));
        toploop thestack stdin)

let interact () =
    let thestack : bigint Stack.t = Stack.create ()
    in  toploop thestack stdin

let _ = if not !Sys.interactive then readfiles ()

