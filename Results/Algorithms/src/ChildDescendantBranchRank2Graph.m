format long
A = [
	0	1.849200	0.942000;
	1	3.462900	2.216400;
	2	11.725700	4.338600;
	3	222.854400	7.979800;
];

hold on
f = plot(A(:,1), A(:,2), 'k-o');
f = plot(A(:,1), A(:,3), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/ChildDescendantBranchRank2Graph.png');
