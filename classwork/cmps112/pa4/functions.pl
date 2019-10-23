/* $Id: functions.pl,v 1.3 2016-11-08 15:04:13-08 - - $ 
 NAME
	functions.pl - 

SYNOPSIS
	functions.pl - fun(airport1,airport2).
	
DESCRIPTION
	This file is used to check if flights are available between given airports

PARTNERS
	Michael Quan midquan@ucsc.edu
	Daniel Lung dlung@ucsc.edu
*/

mathfns( X, List ) :-
   S is sin( X ),
   C is cos( X ),
   Q is sqrt( X ),
   List = [S, C, Q].

constants( List ) :-
   Pi is pi,
   E is e,
   Epsilon is epsilon,
   List = [Pi, E, Epsilon].

sincos( X, Y ) :-
   Y is sin( X ) ** 2 + cos( X ) ** 2.
   

/* Converts Latitudes and Longitudes into Radians then Haversines them then divides by 500 mph  */
latLonToTime( Lat1, Lon1, Lat2, Lon2, Converted ) :-
	degmin_to_radian( Lat1, RLat1 ),
	degmin_to_radian( Lon1, RLon1 ),
	degmin_to_radian( Lat2, RLat2 ),
	degmin_to_radian( Lon2, RLon2 ),
	haversine_radians( RLat1, RLon1, RLat2, RLon2, Distance),
	distanceToTime( Distance, Converted).

/* Converter for Degrees and Minutes to Radians */
degmin_to_radian( degmin( Degree, Minutes ), Radians ) :-
	Degrees is Degree + Minutes / 60,
	Radians is Degrees * pi / 180.

/* Starter code that finds circle distance */
haversine_radians( Lat1, Lon1, Lat2, Lon2, Distance ) :-
    Dlat is Lat2 - Lat1,
    Dlon is Lon2 - Lon1,
    A is sin( Dlat / 2 ) ** 2
        + cos( Lat1 ) * cos( Lat2 ) * sin( Dlon / 2 ) ** 2,
    Dist is 2 * atan2( sqrt( A ), sqrt( 1 - A )),
    Distance is Dist * 3961.


/* Calculates total flight time given arrival and departure airports */
totalFlightTime( DAirport, AAirport, FlightTime ) :-
    airport( DAirport, _, Lat1, Lng1 ),
    airport( AAirport, _, Lat2, Lng2 ),
    latLonToTime( Lat1, Lng1, Lat2, Lng2, FlightTime).

/* Calculate Arrival Time from DAirport to AAirport */
arrivalTime( flight(DAirport, AAirport, time( Hours,Minutes )), ArrivalTime) :-
    totalFlightTime( DAirport, AAirport, FlightTime ),
	conv_hours( Hours, Minutes, DepartureTime),
    ArrivalTime is DepartureTime + FlightTime. 

/* Prints Time in the Given Format with TotalTime */
timePrinter( TotalTime ) :-
	find_floor( TotalTime, Floored),
    Hours is Floored // 60,
    Minutes is Floored mod 60,
	print_mins( Hours), print( : ), 
	print_mins( Minutes ).

/* Prints out 0 if blank or less than 10 */
print_mins( Minutes ):- 
	( Minutes < 10 
		-> print( 0 ), print( Minutes )
		
		; print( Minutes )
	).
	
/* Helper functions to convert values from one to another */
	
/* Converts hours and minutes to only total hours */
conv_hours( Hours, Minutes, TotalHours ) :-
    TotalHours is Hours + Minutes / 60.
	
/* Converts distance into time by given 500 mph speed */	
distanceToTime( Distance, Time ) :-
	Time is Distance / 500.

/* Converts to minutes and floors it to keep it as an integer */
find_floor( TotalTime, Floored ) :-
	conv_minutes( TotalTime, Minutes),
	Floored is floor( Minutes ).

/* Converts minutes to hours */
conv_minutes( Hours, Minutes ) :-
    Minutes is Hours * 60.

conv_minutes( Hours, Minutes, TotalMinutes ) :-
    TotalMinutes is Minutes + Hours * 60.

	
/* Writes Path by using given data and timePrinter to be used */
writePath( [flight(Depart, Arrive, time(Hours, Minutes))|List]) :-
	airport( Depart, DAirport, _, _),
	airport( Arrive, AAirport, _, _),
	conv_hours( Hours, Minutes, DepartTime ),
	arrivalTime( flight(Depart, Arrive, time(Hours, Minutes)), ArrivalTime),
	write( 'depart ' ), write( Depart ), write( ' '),
	write( DAirport), write( ' '), timePrinter( DepartTime ), nl,
	write( 'arrive ' ), write( Arrive ), write( ' '),
	write( AAirport), write( ' '), timePrinter( ArrivalTime ), nl,
	writePath( List ).
	
writePath( [] ).

/* If both depart and arrive are flyable this will be called */
fly( Depart, Arrive ) :-
    listpath( Depart, Arrive, List), nl,
    writePath(List), !.
	
/* If both depart and arrive exsist but are no path is found, this will be called */
fly( Depart ,Arrive ) :-
	not( Depart = Arrive),
	write( 'No flight path available from '), write( Depart ), 
	write( ' to '), write( Arrive), write('.'),nl,
	!, fail.

/* If depart doesn't exsist, this will be called */	
fly( Depart ,_ ) :-
	not(airport(Depart, _, _, _)),n1,
	write( Depart ), write( 'is not a valid airport.'),nl,
	!, fail.

/* If arrive doesn't exsist, this will be called */	
fly( _, Arrive ) :-
	not(airport(Arrive, _, _, _)),n1,
	write( Arrive ), write( 'is not a valid airport.'),nl,
	!, fail.
	
/* If both don't exsist, this will be called */		
fly( Depart, Arrive) :-
	not(airport(Depart, _, _, _)),
	not(airport(Arrive, _, _, _)),n1,
	write(Depart), write(' and '),
	write( Arrive ), write( 'are not valid airports.'),nl,
	!, fail.

	
/* If the same airport is called for depart and arrive this will be called */
fly( Depart, Depart ) :-
	write( 'The departure and arrival airport ('), write(Depart),
	write(') are the same.'), 
	!, fail.

/*Helper functions for listpath */
	
/* Checks to see if enough time to transfer from flights */
transferTime( TimeLanded, time( Hours, Minutes )) :-
    conv_minutes( TimeLanded, MinuteLanded ),
    conv_minutes( Hours, Minutes, MinuteLeaving ),
	Layover is MinuteLanded + 29,
    Layover < MinuteLeaving.

/* Checks to see if flights are overnight, if so path is not available */
checkOvernight( flight( Dep,Arr,DepTime )) :-
   arrivalTime( flight( Dep,Arr,DepTime ), ArrivTime ),
   ArrivTime < 24.
   
/* Prolog's version of not given by Examples */
not( X ) :- X, !, fail.
not( _ ).


listpath( Depart, Depart, _, [] ).

/* Creates a list from Node to End */
listpath( Depart, Arrive, [flight( PrevDep, PrevArr, PrevDepTime )| Tried],
    [flight( Depart, Next, NextDep )| List] ) :-
    flight( Depart, Next, NextDep),
    arrivalTime( flight( PrevDep, PrevArr, PrevDepTime ), PrevArriv),
    transferTime( PrevArriv, NextDep ),
    checkOvernight( flight( Depart, Next, NextDep )),
    Tried2 = append( [flight( PrevDep, PrevArr, PrevDepTime )], Tried ),
	
	/* Makes sure and checks that Next is not already tried or previous arrival */
    not( member( Next, Tried2 )), 
	not( Next = PrevArr ),
    listpath( Next, Arrive,[flight( Depart, Next, NextDep )|Tried2],List ).
	
listpath( Depart, Arrive, [flight( Depart, Next, NextDep)|Listed] ) :-
	/* Checks to make sure depart and arrival are different airports */
    not(Depart = Arrive),
    flight(Depart, Next, NextDep),
    listpath( Next, Arrive, [flight( Depart, Next, NextDep)], Listed ).
	
