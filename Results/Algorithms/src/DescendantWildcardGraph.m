format long
A = [
	0	1.964200	0.945500;
	1	2.554800	1.803900;
	2	4.817600	1.580800;
	3	8.024700	1.902700;
	4	16.045400	2.261900;
	5	30.718800	2.599400;
	6	66.052200	2.962100;
	7	148.574200	3.444600;
	8	316.154600	3.601000;
	9	692.754700	3.872400;
	10	1524.160600	4.277100;
];

hold on
f = plot(A(:,1), A(:,2), 'k-o');
f = plot(A(:,1), A(:,3), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/DescendantWildcardGraph.png');
