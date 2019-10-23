COPY Lab4.TaxReturns FROM stdin USING DELIMITERS '|';
112|2017|I|11/01/2017|124343.45|4567
112|2016|I|08/14/2016|76543.50|987
112|2015|I|09/03/2015|4323646|98759
112|2014|I|09/03/2014|243456|8452
113|2017|I|07/04/2017|23455|239
113|2016|I|01/22/2016|9823.67|99
114|2016|B|07/04/2016|2345564.55|98438.60
115|2017|B|07/27/2017|32221223.88|123789.89
115|2015|B|09/18/2015|43534498.45|678877
116|2017|I|06/29/2017|294649.00|6723
117|2017|B|01/31/2017|23444334.78|739567.78
118|2016|I|02/22/2016|745697.54|56777.8
119|2016|I|09/27/2016|6465004|34947.09
120|2016|B|04/16/2017|92659563.77|9948678.9
120|2015|B|02/06/2015|192365838.6|76207494
121|2017|I|04/03/2017|89043.37|569
121|2016|I|02/02/2016|654290.70|890.6
121|2015|I|04/21/2015|325633.5|45098.67
121|2014|I|04/21/2014|83465.56|23478.31
122|2017|B|03/08/2017|890653878.89|5678998.20
123|2016|B|12/01/2016|987124690.43|1429580.82
\.

COPY Lab4.Payments FROM stdin USING DELIMITERS '|';
112|03/05/2017|8597.00
112|03/11/2016|1870.2
112|04/15/2015|108955.73
112|02/02/2014|3456.00
113|05/06/2017|873.34
113|05/13/2016|201.7
115|03/21/2017|223683.65
116|01/03/2017|6785
118|02/06/2016|86787.5
119|09/21/2016|36647.09
120|03/01/2017|10348699.4
120|01/26/2015|79590491
121|04/03/2017|700
121|02/02/2016|1000.3
121|02/11/2015|47798.67
122|01/19/2017|5678998.20
122|03/22/2015|194639.44
123|12/01/2016|1429580.82
124|11/04/2017|4882548.55
\.

COPY Lab4.Individuals FROM stdin USING DELIMITERS '|';
110|Jin Huff|843 Ante Ave|111|01/03/2016|12/11/2016|18767.55
111|Kylan Young|Ap 544-8986 Massa Rd.|110|05/12/2017|11/23/2017|20934.00
112|Channing Cameron|8981 Id Rd.|141|11/01/2017|03/05/2017|8597.00
113|Steel Joyner|176 Atta Road|125|07/04/2017|05/06/2017|239
116|Sophia Nieves|P.O. Box 428, 6356 Nonummy Ave|124|06/29/2017|03/29/2017|6723
118|Quinn Hayes|6609 Parturient Road|\N|02/22/2016|02/06/2016|56777.8
119|Kim Barton|Ap 268-138 Enim. Rd.|128|09/27/2017|09/21/2016|48750.13
121|Leslie Valentine|843 Ante Ave|100|04/03/2017|04/03/2017|569
124|Vernon Evans|945 Ligula Rd.|116|03/08/2017|01/19/2017|5678998.20
125|Stacy Morris|P.O. Box 865, 3179 Arcu. Ave|113|01/23/2015|03/22/2014|3957.4
126|Eden Valentine|486 Phasellus St.|\N|11/19/2016|08/30/2016|3885883.90
127|Jaime Hogan|1727 Nisl. Ave|133|09/21/2016|10/23/2016|48577.23
128|Randall Mullins|P.O. Box 933, 2358 Nulla St.|119|08/09/2016|03/16/2016|456
130|Neil Sosa|4638 Dictum. Rd.|\N|12/31/2014|12/12/2014|3999.99
133|Paula Trevino|531-6781 Arcu. Street|127|07/27/2017|05/22/2017|18493.44
136|Melinda Weiss|714-2638 Fringilla Street|139|10/12/2017|09/24/2017|2344
\.

COPY Lab4.Businesses FROM stdin USING DELIMITERS '|';
107|Velit Dui Semper Consulting|Ap #266-4576 Nulla Av.|P|03/12/2017|02/11/2017|1845194.46
108|Sed Pede Nec Corporation|4645 Non Av.|C|04/12/2017|02/25/2017|3877644.45
109|EROS Now Corporation|P.O. Box 826, 4614 Est. Rd.|C|11/10/2017|12/23/2016|8723649.00
114|Feugiat Consulting|Ap #690-5592 Et, Street|P|07/04/2016|07/04/2016|98438.60
115|Metus LLC|Ap #843-7480 Sollicitudin St.|L|09/18/2017|03/21/2015|678877
117|TIRUPATI Associates|P.O. Box 716, 2542 Conubia St.|P|01/31/2017|01/31/2017|739567.78
120|Aliquam Rutrum Associates|298-9804 Mi. Road|P|11/16/2017|10/26/2017|9948678.9
122|Maecenas Libero Est Institute|Ap #665-8786 Risus Street|L|03/08/2017|01/19/2017|5678998.20
123|Tirth Lobortis Corp.|Ap #732-2056 Vel Rd.|C|08/07/2016|02/28/2015|2846293.46
129|AMET DIAM Ltd.|843 Ante Ave|L|10/16/2017|08/22/2015|388645
131|Donec Non Consulting|7930 Orci. Av.|P|11/10/2017|12/22/2016|863640.98
132|Talisman Consulting Ltd|Ap #749-9388 Adipiscing St.|L|08/20/2017|07/20/2017|32956295.47
134|Enim Suspendisse Aliquet Corp.|Ap #776-6557 Suspendisse St.|C|08/19/2017|09/09/2016|112398.28
135|LIBERTO Nec Incorporated|834-9462 Aliquam Road|C|07/06/2016|11/24/2015|295735.47
137|Dolor Sit Amet Foundation|Ap #120-954 Consectetuer Rd.|P|06/09/2015|06/08/2015|9946244.34
138|Amet LLP|P.O. Box 990, 7243 In Av.|L|08/09/2017|02/01/2017|72859
139|Pede Institute|779 Quam. St.|C|08/08/2016|09/07/2015|88470.55
140|TIMBERLAKE Woodworks Ltd.|4544 Nobel Dr.|L|06/29/2017|06/29/2017|213432.5
\.

COPY Lab4.IRSAgents FROM stdin USING DELIMITERS '|';
A4DV57|110|1|TRUE
D6DJ79|119|\N|\N
G87FK8|121|3|TRUE
KL98O4|124|2|FALSE
P3E4RR|126|2|FALSE
D9IJ72|127|\N|\N
29SN06|128|3|\N
31AD01|130|4|TRUE
S4TYC8|133|1|FALSE
DF7878|136|3|FALSE
\.

COPY Lab4.Delinquents FROM stdin USING DELIMITERS '|';
107|A4DV57|122
108|DF7878|129
109|S4TYC8|139
111|\N|108
112|\N|135
113|31AD01|108
114|A4DV57|135
117|S4TYC8|120
118|\N|139
125|\N|140
123|DF7878|122
131|A4DV57|132
135|DF7878|138
137|P3E4RR|135
139|\N|140
140|\N|131
141|\N|134