format long
A = [
	0	0.380000	9613.010000	9612.470000;
	1	0.460000	9504.420000	9721.410000;
	2	8.630000	9543.980000	9449.800000;
	3	11.340000	9633.430000	9549.740000;
	4	12.860000	9734.670000	9571.840000;
];

hold on
f = plot(A(:,1), A(:,2), 'k-x');
f = plot(A(:,1), A(:,3), 'k-o');
f = plot(A(:,1), A(:,4), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('None', 'The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/ChildBranchRank2Graph.png');
