format long
A = [
	0	0.360000	9515.220000	9539.700000;
	1	1.810000	9504.810000	9466.360000;
	2	8.620000	9541.530000	9510.840000;
	3	16.910000	9585.640000	9469.100000;
	4	35.650000	9542.170000	9573.000000;
];

hold on
f = plot(A(:,1), A(:,2), 'k-x');
f = plot(A(:,1), A(:,3), 'k-o');
f = plot(A(:,1), A(:,4), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('None', 'The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/ChildBranchDepth2Graph.png');
