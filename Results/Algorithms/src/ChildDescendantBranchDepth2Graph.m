format long
A = [
	0	1.969100	0.929000;
	1	3.414100	2.232800;
	2	11.527600	4.148100;
	3	133.719200	7.112200;
	4	3365.879100	10.947700;
];

hold on
f = plot(A(:,1), A(:,2), 'k-o');
f = plot(A(:,1), A(:,3), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/ChildDescendantBranchDepth2Graph.png');
