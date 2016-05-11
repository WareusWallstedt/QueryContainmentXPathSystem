format long
A = [
	0	1.858600	0.958700;
	1	2.807500	2.436700;
	2	5.754700	4.166600;
	3	9.337600	7.051500;
	4	14.670200	10.924100;
	5	21.003700	16.563400;
	6	28.256200	22.755900;
	7	39.005600	30.915300;
	8	49.993800	35.683100;
	9	65.218200	44.150100;
	10	78.556300	54.781100;
];

hold on
f = plot(A(:,1), A(:,2), 'k-o');
f = plot(A(:,1), A(:,3), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/ChildBranchDepth2Graph.png');
