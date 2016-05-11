format long
A = [
	0	1.565600	0.944200;
	1	2.928800	1.864900;
	2	3.788500	1.612600;
	3	9.803900	1.955100;
	4	10.916200	2.229200;
	5	28.637100	2.615000;
	6	30.242200	2.960200;
	7	100.757700	3.184800;
	8	106.575700	3.968600;
	9	350.137400	3.957000;
	10	366.567100	4.211000;
];

hold on
f = plot(A(:,1), A(:,2), 'k-o');
f = plot(A(:,1), A(:,3), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/ChildDescendantWildcardGraph.png');
