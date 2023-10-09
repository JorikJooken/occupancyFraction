︠c41f38ee-cdbf-4a9a-b0f7-7e0f486aa739s︠
#define a verification of strict majorization

#Check if b majorizes a in a strict way
def Maj(a,b):
    l=len(a);
    if l>len(b):
        print("Problem");
        print(a,b);
    else:
        for k in range(1,l):
            if a[k]*b[k-1]>a[k-1]*b[k]:
                return(False)
                break
    return(True)
︡f00ca14c-a32a-44a8-a8ab-c60666d713eb︡{"done":true}
︠0b3ac2d4-4937-408d-82f4-a5968a12974c︠
#for all graphs of a given order, generate the connected cubic triangle-free graphs of order n
#compute the number of independent sets of a certain size
#compare with the majorized coefficient-sets and check that those are attained
#we do so for graphs of order at most 18

from sage.graphs.independent_sets import IndependentSets

d={6:[[1,6,6,2]], 8:[[1, 8, 16, 8]], 10: [[1, 10, 30, 30, 5]], 12:[[1, 12, 48, 76, 42, 3]], 14:[[1, 14, 70, 154, 147, 48]], 16: [[1, 16, 96, 272, 376, 232, 45]], 18: [[1, 18, 126, 438, 801, 747, 303, 27],[1, 18, 126, 438, 801, 744, 302, 36],[1, 18, 126, 438, 801, 746, 307, 36]]  };
for n in range(6,20,2):
    C=[];
    for g in graphs.nauty_geng('-c -t ' +str(n)+' -d3 -D3'):
        coeff=[];
        I=IndependentSets(g);
        for k in range(g.complement().clique_number() +1):
            coeff.append(len(list(x for x in I if len(x) == k)))
        C.append(coeff)
    for coeff in C:
        maj=False
        for comp in d[n]:
            if Maj(comp, coeff):
                maj=True
        if not maj:
            print(coeff)
    for comp in d[n]:
        if not comp in C:
            print("mistake")
            comp           
︡e96e7559-27ee-4bea-8e45-1a71f5d7a35f︡{"done":true}
︠a302c3df-a208-435a-b741-215a2c4c13d1︠
#generate the critical rational functions alpha_G(x) for the critical graphs with order at most 18
for n in range(6,20,2):
    for coeff in d[n]:
        p=sum(c*x**i for i,c in enumerate(coeff))
        diff(p)*x/p/g.order()
︡80305970-db3e-4188-93dc-adcb06ee8bb8︡{"stdout":"3/7*(x^2 + 2*x + 1)*x/(2*x^3 + 6*x^2 + 6*x + 1)\n4/7*(3*x^2 + 4*x + 1)*x/(8*x^3 + 16*x^2 + 8*x + 1)\n5/7*(2*x^3 + 9*x^2 + 6*x + 1)*x/(5*x^4 + 30*x^3 + 30*x^2 + 10*x + 1)\n3/14*(5*x^4 + 56*x^3 + 76*x^2 + 32*x + 4)*x/(3*x^5 + 42*x^4 + 76*x^3 + 48*x^2 + 12*x + 1)\n1/7*(120*x^4 + 294*x^3 + 231*x^2 + 70*x + 7)*x/(48*x^5 + 147*x^4 + 154*x^3 + 70*x^2 + 14*x + 1)\n1/7*(135*x^5 + 580*x^4 + 752*x^3 + 408*x^2 + 96*x + 8)*x/(45*x^6 + 232*x^5 + 376*x^4 + 272*x^3 + 96*x^2 + 16*x + 1)\n9/14*(21*x^6 + 202*x^5 + 415*x^4 + 356*x^3 + 146*x^2 + 28*x + 2)*x/(27*x^7 + 303*x^6 + 747*x^5 + 801*x^4 + 438*x^3 + 126*x^2 + 18*x + 1)\n3/7*(42*x^6 + 302*x^5 + 620*x^4 + 534*x^3 + 219*x^2 + 42*x + 3)*x/(36*x^7 + 302*x^6 + 744*x^5 + 801*x^4 + 438*x^3 + 126*x^2 + 18*x + 1)\n1/7*(126*x^6 + 921*x^5 + 1865*x^4 + 1602*x^3 + 657*x^2 + 126*x + 9)*x/(36*x^7 + 307*x^6 + 746*x^5 + 801*x^4 + 438*x^3 + 126*x^2 + 18*x + 1)\n"}︡{"done":true}
︠05a099b7-de82-4c90-9511-62b107d6553c︠

#verify the 4 important graphs for conjecture 2, i.e. the ones that prove that conjecture 2 is false

G=[]
SS=["IsP@OkWHG","MsP@P?WCOI?a?a?H_","Ms?G?DCQ@DAID_IO?", "SsP@P?SCOO?`?_?O_C??`?A_?C_?A_??["];
for ss in SS:
    from sage.graphs.graph_input import from_graph6
    H = Graph();
    from_graph6(H,ss)
    G.append(H)
for g in G:
    coeff=[];
    for k in range(g.complement().clique_number() +1):
        coeff.append(len(list(x for x in IndependentSets(g) if len(x) == k)))
    p=sum(c*x**i for i,c in enumerate(coeff))
    diff(p)*x/p/g.order()
︡a42fa853-6310-4892-ba7b-aa061d9fe662︡{"stdout":"(2*x^3 + 9*x^2 + 6*x + 1)*x/(5*x^4 + 30*x^3 + 30*x^2 + 10*x + 1)\n1/7*(120*x^4 + 294*x^3 + 231*x^2 + 70*x + 7)*x/(48*x^5 + 147*x^4 + 154*x^3 + 70*x^2 + 14*x + 1)\n1/2*(35*x^4 + 84*x^3 + 66*x^2 + 20*x + 2)*x/(49*x^5 + 147*x^4 + 154*x^3 + 70*x^2 + 14*x + 1)\n(2*x^7 + 112*x^6 + 372*x^5 + 478*x^4 + 302*x^3 + 99*x^2 + 16*x + 1)*x/(5*x^8 + 320*x^7 + 1240*x^6 + 1912*x^5 + 1510*x^4 + 660*x^3 + 160*x^2 + 20*x + 1)\n"}︡{"done":true}
︠65c06fc3-bf08-4c97-ab6a-3b4886d74366︠

#verify the 2 important graphs for conjecture 3
#Hereby the total number of independent sets for G_{38} is computed as a check
G=[]
SS=["]s??????????B??o?C_?o?W?AO?AO?CG?G_?@C??GG?@@??O?o?O?K?C??c?_?O_C??P?_?AG?","es????FA?O@?@??_?_?C??O?@?????????I??CO??H??@?_?@C??CA???OO??AA???GO???Q????I????S?@???O_G??GC?_??AOA???__G??A?OO???__?"];
for ss in SS:
    from sage.graphs.graph_input import from_graph6
    H = Graph();
    from_graph6(H,ss)
    G.append(H)
g=G[0]
coeff=[];
for k in range(g.complement().clique_number() +1):
    coeff.append(len(list(x for x in IndependentSets(g) if len(x) == k)))
p=sum(c*x**i for i,c in enumerate(coeff))
diff(p)*x/p/g.order()


︡fd723545-e29e-49f6-b687-2187a9254af7︡{"stdout":"(x^14 + 14*x^13 + 104*x^12 + 548*x^11 + 2354*x^10 + 8316*x^9 + 19827*x^8 + 29660*x^7 + 28161*x^6 + 17322*x^5 + 6956*x^4 + 1802*x^3 + 289*x^2 + 26*x + 1)*x/(2*x^15 + 30*x^14 + 240*x^13 + 1370*x^12 + 6420*x^11 + 24948*x^10 + 66090*x^9 + 111225*x^8 + 120690*x^7 + 86610*x^6 + 41736*x^5 + 13515*x^4 + 2890*x^3 + 390*x^2 + 30*x + 1)\n"}︡{"done":true}
︠5259a8ba-0d93-4b7e-8d77-9253e6540ecbs︠
g=G[1]
IndependentSets(g).cardinality()
coeff=[1,38,646,6498,43111,199120,658882,1583954,2777315,3537622,3238356,2097330,947518,300924,72142,14802,2660,380,38,2];
sum(coeff)
p=sum(c*x**i for i,c in enumerate(coeff))
diff(p)*x/p/g.order()

︡6a9230cf-7577-440d-8e17-40bf56664c67︡{"stdout":"15481339"}︡{"stdout":"\n"}︡{"stdout":"15481339\n"}︡{"stdout":"1/19*(19*x^18 + 342*x^17 + 3230*x^16 + 21280*x^15 + 111015*x^14 + 504994*x^13 + 1956006*x^12 + 5685108*x^11 + 11535315*x^10 + 16191780*x^9 + 15919299*x^8 + 11109260*x^7 + 5543839*x^6 + 1976646*x^5 + 497800*x^4 + 86222*x^3 + 9747*x^2 + 646*x + 19)*x/(2*x^19 + 38*x^18 + 380*x^17 + 2660*x^16 + 14802*x^15 + 72142*x^14 + 300924*x^13 + 947518*x^12 + 2097330*x^11 + 3238356*x^10 + 3537622*x^9 + 2777315*x^8 + 1583954*x^7 + 658882*x^6 + 199120*x^5 + 43111*x^4 + 6498*x^3 + 646*x^2 + 38*x + 1)\n"}︡{"done":true}
︠519904ae-0279-42b7-99fe-06a059d2b083︠

#verify the 2 important graphs for conjecture 4, to conclude the conjecture is false
G=[]
SS=["Ys_?????????????GwA?wOGoco?WQ?gK?`I?G`O?dO?AIG?Ac_?AX???","_s_???C@?G?_?O?_?O?A??O?@??C??C??O_oGGAOP?KG@C_O@COOCA_CAS??Oa_?G@P??OHG??OSA??_KC??"];
for ss in SS:
    from sage.graphs.graph_input import from_graph6
    H = Graph();
    from_graph6(H,ss)
    G.append(H)
for g in G:
    coeff=[];
    for k in range(g.complement().clique_number() +1):
        coeff.append(len(list(x for x in IndependentSets(g) if len(x) == k)))
    p=sum(c*x**i for i,c in enumerate(coeff))
    diff(p)*x/p/g.order()
︡d17f0ffc-18f7-4915-8dea-5e49cce6b562︡{"stdout":"(x^12 + 12*x^11 + 66*x^10 + 230*x^9 + 576*x^8 + 1128*x^7 + 1890*x^6 + 2316*x^5 + 1725*x^4 + 736*x^3 + 174*x^2 + 21*x + 1)*x/(2*x^13 + 26*x^12 + 156*x^11 + 598*x^10 + 1664*x^9 + 3666*x^8 + 7020*x^7 + 10036*x^6 + 8970*x^5 + 4784*x^4 + 1508*x^3 + 273*x^2 + 26*x + 1)"}︡{"stdout":"\n(x^15 + 15*x^14 + 105*x^13 + 468*x^12 + 1509*x^11 + 3795*x^10 + 7910*x^9 + 14490*x^8 + 21549*x^7 + 22610*x^6 + 15513*x^5 + 6780*x^4 + 1851*x^3 + 303*x^2 + 27*x + 1)*x/(2*x^16 + 32*x^15 + 240*x^14 + 1152*x^13 + 4024*x^12 + 11040*x^11 + 25312*x^10 + 51520*x^9 + 86196*x^8 + 103360*x^7 + 82736*x^6 + 43392*x^5 + 14808*x^4 + 3232*x^3 + 432*x^2 + 32*x + 1)"}︡{"stdout":"\n"}︡{"done":true}
︠caebfec3-fab8-4acc-99c6-b9f5b3cdca99︠

#verify the 4 important graphs for conjecture 5, to conclude the conjecture is false
G=[]
SS=["Ls`?XGRQR@B`Kc","Rs_?I@?O?`CAAOHQ@R@DCBH?RC?gc?","S@?IC?g@S_P?@aOWOS@ACSD@GGPCg?gB?","UIAC@OOA_H@@?Qo?c_?cH@O?OQD?GIC?OG_`?KQ?"];
for ss in SS:
    from sage.graphs.graph_input import from_graph6
    H = Graph();
    from_graph6(H,ss)
    G.append(H)
for g in G:
    coeff=[];
    for k in range(g.complement().clique_number() +1):
        coeff.append(len(list(x for x in IndependentSets(g) if len(x) == k)))
    p=sum(c*x**i for i,c in enumerate(coeff))
    diff(p)*x/p/g.order()
︡79c8e4a9-db27-4588-bd99-abc5c48d3773︡{"stdout":"(12*x^3 + 18*x^2 + 8*x + 1)*x/(39*x^4 + 78*x^3 + 52*x^2 + 13*x + 1)\n1/19*(28*x^6 + 822*x^5 + 2580*x^4 + 2812*x^3 + 1311*x^2 + 266*x + 19)*x/(4*x^7 + 137*x^6 + 516*x^5 + 703*x^4 + 437*x^3 + 133*x^2 + 19*x + 1)\n1/5*(28*x^6 + 492*x^5 + 1110*x^4 + 988*x^3 + 405*x^2 + 75*x + 5)*x/(16*x^7 + 328*x^6 + 888*x^5 + 988*x^4 + 540*x^3 + 150*x^2 + 20*x + 1)\n1/2*(8*x^7 + 168*x^6 + 672*x^5 + 975*x^4 + 652*x^3 + 216*x^2 + 34*x + 2)*x/(11*x^8 + 264*x^7 + 1232*x^6 + 2145*x^5 + 1793*x^4 + 792*x^3 + 187*x^2 + 22*x + 1)\n"}︡{"done":true}
︠81cddcc7-8a8b-484d-a508-092850b5dc32︠









