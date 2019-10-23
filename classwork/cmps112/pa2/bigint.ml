(* $Id: bigint.ml,v 1.5 2014-11-11 15:06:24-08 - - $ 

NAME
	bigint.ml - big int module 

SYNOPSIS
	bigint.ml

DESCRIPTION
	This file creates the Bigint and all of its functions. It is called by the maindc.ml file to create the ocamldc.

PARTNERS
	Daniel Lung dlung@ucsc.edu
	Michael Quan midquan@ucsc.edu
*)

open Printf

module Bigint = struct

    type sign     = Pos | Neg
    type bigint   = Bigint of sign * int list
    let  radix    = 10
    let  radixlen =  1

	let listlen	  = List.length
    let listrev   = List.rev_map
	let car       = List.hd
    let cdr       = List.tl
    let map       = List.map
    let reverse   = List.rev
    let strcat    = String.concat
    let strlen    = String.length
    let strsub    = String.sub
    let zero      = Bigint (Pos, [])
	
	(*Given functions from starter code *)
    let charlist_of_string str = 
        let last = strlen str - 1
        in  let rec charlist pos result =
            if pos < 0
            then result
            else charlist (pos - 1) (str.[pos] :: result)
        in  charlist last []


    let bigint_of_string str =
        let len = strlen str
        in  let to_intlist first =
                let substr = strsub str first (len - first) in
                let digit char = int_of_char char - int_of_char '0' in
                map digit (reverse (charlist_of_string substr))
            in  if   len = 0
                then zero
                else if   str.[0] = '_'
                     then Bigint (Neg, to_intlist 1)
                     else Bigint (Pos, to_intlist 0)

    let string_of_bigint (Bigint (sign, value)) =
        match value with
        | []    -> "0"
        | value -> let reversed = reverse value
                   in  strcat ""
                       ((if sign = Pos then "" else "-") ::
                        (map string_of_int reversed))
						
	(* trims zeros in a list, based off of trimzeros.ml starter code *)
	let trim list =
	let rec trim' list' = match list' with
        | []       -> []
        | [0]      -> []
        | car::cdr ->
             let cdr' = trim' cdr
             in  match car, cdr' with
                 | 0, [] -> []
                 | car, cdr' -> car::cdr'
    in trim' list
												
	let rec cmp' list1 list2 = 
		if (car list1) > (car list2) 
			then 1
		else if (car list1) < (car list1) 
			then -1
		else 
			cmp' (cdr list1) (cdr list2)
			

	let cmp list1 list2 = 
		if (listlen list1) > (listlen list2)
			then 1 
		else if (listlen list1) < (listlen list2)
			then -1 
		else 
			cmp' (reverse list1) (reverse list2)

	(* recursive helper function to add called by both add and sub from starter code *)
    let rec add' list1 list2 carry = match (list1, list2, carry) with
        | list1, [], 0       -> list1
        | [], list2, 0       -> list2
        | list1, [], carry   -> add' list1 [carry] 0
        | [], list2, carry   -> add' [carry] list2 0
        | car1::cdr1, car2::cdr2, carry ->
          let sum = car1 + car2 + carry
          in  sum mod radix :: add' cdr1 cdr2 (sum / radix)
		  
	(* recursive helper function to sub called by both add and sub based off of starter code *)	  
	let rec sub' list1 list2 borrow = match (list1, list2, borrow) with
		| list1, [], 0       -> list1
        | [], list2, 0       -> list2
        | list1, [], borrow   -> trim (sub' list1 [borrow] 0)
        | [], list2, borrow   -> trim (sub' [borrow] list2 0)
        | car1::cdr1, car2::cdr2, borrow ->
			let diff = car1 - car2 - borrow
			in if diff >= 0
				then car1 - car2 - borrow :: trim (sub' cdr1 cdr2 0)
			else 
				car1 + radix - car2 - borrow :: trim (sub' cdr1 cdr2 1)

	(* add function compares sign and values then decides how to do addition*)
    let add (Bigint (neg1, value1)) (Bigint (neg2, value2)) =
        if neg1 = neg2 
			then Bigint (neg1, add' value1 value2 0)
        else if (cmp value1 value2) = 1 (* if value1 > value2 *) 
			then Bigint(neg1, trim (sub' value1 value2 0))
		else if (cmp value1 value2) = -1 (* if value1 < value2 *) 
			then Bigint(neg2, trim (sub' value2 value1 0))
		else 
			zero

	(* sub function compares sign and values then decides how to do addition*)
    let sub (Bigint (neg1, value1)) (Bigint (neg2, value2)) =

        if (neg1 = Neg && neg2 = Neg) then 
            if (cmp value1 value2) = 1 (* if value1 > value2 *) 
				then Bigint(neg1, add' value1 value2 0)
            else 
				Bigint(Pos, trim (sub' value2 value1 0))
		else if (neg1 = Pos && neg2 = Pos) then 
            if (cmp value1 value2) = 1 (* if value1 > value2 *) 
				then Bigint (neg1, trim (sub' value1 value2 0))
            else 
				Bigint (Neg, trim (sub' value2 value1 0))
        else 
			Bigint(neg1, add' value1 value2 0)

	let list_comp list1 list2 = 
		let value1 = float_of_string (strcat "" 
            (listrev string_of_int list1))
		and value2 = float_of_string (strcat "" 
            (listrev string_of_int list2))
		in if (value1 > value2) 
			then 1
		else 
			-1 
	
	let double number = add' number number 0
	
	(* recursive helper function to mul called by mul based off of starter code *)
	let rec  mul' list1 powerof2 list2 = 
        if (list_comp powerof2 list1) = 1 (* if powerof2 > list1 *) 
			then list1, [0]
        else let remainder, product =
            mul' list1 (double powerof2) (double list2)
        in if (list_comp powerof2 remainder) = 1 (* if powerof2 > remainder *) 
            then remainder, product
            else 
				(sub' remainder powerof2 0), (add' product list2 0)
				
	(* multiply function used from starter code modified for Bigint's sign *)      
    let mul (Bigint (neg1, value1)) (Bigint (neg2, value2)) =
        if neg1 = neg2
			then let _, product = 
            mul' value1 [1] value2 in Bigint(Pos, product)
        else let _, product = 
            mul' value1 [1] value2 in Bigint(Neg, product)
			
	(* recursive helper function to div called by divrem based off of starter code *)
    let rec divrem' list1 powerof2 list2 =
		if (list_comp list2 list1) = 1 (* if list2 > list1 *) 
			then [0], list1
        else let quotient, remainder =
            divrem' list1 (double powerof2) (double list2) in
            if (list_comp list2 remainder) = 1 (* if list2 > remainder *)
				then quotient, remainder
            else 
				(add' quotient powerof2 0), (sub' remainder list2 0)

    let divrem list1 list2 = divrem' list1 [1] list2

	(* divide function used from starter code modified for Bigint's sign *)
    let div (Bigint (neg1, value1)) (Bigint (neg2, value2)) =
        if neg1 = neg2
			then let quotient, _ = 
            divrem value1 value2 in Bigint(Pos, quotient)
        else let quotient, _ = 
            divrem value1 value2 in Bigint(Neg, quotient)
			
	(* remainder function used from starter code modified for Bigint's sign *)
    let rem (Bigint (neg1, value1)) (Bigint (neg2, value2)) =
        if neg1 = neg2
			then let _, remainder = 
            divrem value1 value2 in Bigint(Pos, remainder)
        else let _, remainder = 
            divrem value1 value2 in Bigint(Neg, remainder)
			
	let pow = add

	(* Attempted making pow function however could not get it to compile and work *)
	(*
	let even number =
		let remainder = trim(even_power(number, [2])) in 
		if cmp remainder [] = 0
			then true
		else
			false
			
	let rec pow' (base, expt, result) = match expt with
		| 0                   -> result
		| expt when even expt -> pow' (let _,power = mul base [1] base in power)
										(let quantity,_ = divrem expt [1] [2] in quantity) result
		
		| expt                -> pow' base (sub' expt [1] 0) (mul base [1] result)

	let pow (Bigint (neg1, value1)) (Bigint (neg2, value2)) =
		if neg2 = Neg 
			then zero 
		else 
			Bigint (Pos, pow (value1, value2, [1]))
	*)
	
end
