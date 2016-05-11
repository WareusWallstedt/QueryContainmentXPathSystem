format long
A = [
	0	1.860000	0.958200;
	1	2.001300	2.092400;
	2	2.953900	2.187300;
	3	3.202000	1.914600;
	4	3.542400	2.322900;
	5	3.977200	2.622800;
	6	4.716500	3.044200;
	7	5.307200	3.535200;
	8	5.912600	3.496100;
	9	6.128500	3.919700;
	10	6.882000	4.246300;
];

hold on
f = plot(A(:,1), A(:,2), 'k-o');
f = plot(A(:,1), A(:,3), 'k-*');
hold off
xlabel('Query Size')
ylabel('Run Time')
legend('The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')
saveas(f, '../img/ChildWildcardGraph.png');
