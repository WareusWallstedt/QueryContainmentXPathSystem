format long
A = [
	0	1.777800	0.948700;
	1	2.820200	2.355000;
	2	5.252900	4.195700;
	3	8.956700	7.150200;
	4	13.972100	10.928100;
	5	20.299900	16.647100;
	6	29.564000	22.704100;
	7	38.301300	30.918000;
	8	51.196300	34.440300;
	9	63.190900	43.916400;
	10	79.438800	56.341000;
];

hold on
f = plot(A(:,1), A(:,2), 'k-o');
f = plot(A(:,1), A(:,3), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/ChildBranchDepth2Graph.png');
