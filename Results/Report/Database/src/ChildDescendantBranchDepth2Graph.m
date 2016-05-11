format long
A = [
	0	0.380000	9473.370000	9559.960000;
	1	1.800000	9568.080000	9511.310000;
	2	14.570000	9554.640000	9508.480000;
	3	19.050000	9699.230000	9563.470000;
	4	55.760000	13921.910000	9672.280000;
];

hold on
f = plot(A(:,1), A(:,2), 'k-x');
f = plot(A(:,1), A(:,3), 'k-o');
f = plot(A(:,1), A(:,4), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('None', 'The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/ChildDescendantBranchDepth2Graph.png');
