format long
A = [
	0	1.723900	0.930300;
	1	2.066300	1.812000;
	2	2.673500	1.632500;
	3	3.412900	2.067400;
	4	3.893100	2.308800;
	5	4.083000	2.593000;
	6	4.810500	3.446500;
	7	5.551000	3.175300;
	8	5.924400	3.604800;
	9	6.143900	3.965300;
	10	6.953600	4.223700;
];

hold on
f = plot(A(:,1), A(:,2), 'k-o');
f = plot(A(:,1), A(:,3), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/ChildGraph.png');
