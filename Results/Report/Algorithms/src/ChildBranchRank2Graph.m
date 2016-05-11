format long
A = [
	0	1.669900	0.952000;
	1	2.755000	2.235000;
	2	5.216700	4.529600;
	3	11.255300	8.360000;
	4	20.879300	15.779500;
	5	42.275800	32.618000;
	6	88.974300	56.506200;
	7	177.079100	115.715000;
	8	356.189700	233.905100;
	9	744.738100	480.637500;
	10	1448.728900	1093.394800;
];

hold on
f = plot(A(:,1), A(:,2), 'k-o');
f = plot(A(:,1), A(:,3), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/ChildBranchRank2Graph.png');
