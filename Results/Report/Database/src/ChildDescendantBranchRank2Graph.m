format long
A = [
	0	0.370000	9549.050000	9499.690000;
	1	0.470000	9481.310000	9569.110000;
	2	14.440000	9562.990000	9638.650000;
	3	13.410000	10471.190000	9621.810000;
	4	14.030000	432669.000000	9587.880000;
];

hold on
f = plot(A(:,1), A(:,2), 'k-x');
f = plot(A(:,1), A(:,3), 'k-o');
f = plot(A(:,1), A(:,4), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('None', 'The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/ChildDescendantBranchRank2Graph.png');
