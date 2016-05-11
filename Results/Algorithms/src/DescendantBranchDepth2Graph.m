format long
A = [
	0	1.910400	0.957400;
	1	4.881600	2.269900;
	2	87.964900	4.249200;
	3	11672.918800	7.886300;
];

hold on
f = plot(A(:,1), A(:,2), 'k-o');
f = plot(A(:,1), A(:,3), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/DescendantBranchDepth2Graph.png');
