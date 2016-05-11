#!/bin/bash

# Arguments:
#  - $1 = test
#  - $2 = filename
#  - $3 = Query Size
function algorithm_test {
	echo "format long" > Results/Algorithms/src/$2.m
	echo "A = [" >> Results/Algorithms/src/$2.m

	for i in $(seq 0 $3)
	do
		if [[ $1 == "child" ]]
		then
			Q1=$(
				echo -en "/root"
				for j in $(seq 1 $i)
				do
					echo -en "/a"$j
				done
			)
		elif [[ $1 == "descendant" ]]
		then
			Q1=$(
				echo -en "/root"
				for j in $(seq 1 $i)
				do
					echo -en "//a"$j
				done
			)
		elif [[ $1 == "child-descendant" ]]
		then
			Q1=$(
				echo -en "/root"
				for j in $(seq 1 $i)
				do
					if [[ $(($j & 1)) -eq 0 ]]
					then
						echo -en "/a"$j
					else
						echo -en "//a"$j
					fi
				done
			)
		elif [[ $1 == "child-wildcard" ]]
		then
			Q1=$(
				echo -en "/root"
				for j in $(seq 1 $i)
				do
					echo -en "/*"
				done
			)
		elif [[ $1 == "descendant-wildcard" ]]
		then
			Q1=$(
				echo -en "/root"
				for j in $(seq 1 $i)
				do
					echo -en "//*"
				done
			)
		elif [[ $1 == "child-descendant-wildcard" ]]
		then
			Q1=$(
				echo -en "/root"
				for j in $(seq 1 $i)
				do
					if [[ $(($j & 1)) -eq 0 ]]
					then
						echo -en "/*"
					else
						echo -en "//*"
					fi
				done
			)
		elif [[ $1 == "child-branch-depth2" ]]
		then
			Q1=$(./create_tree child 2 $i)
		elif [[ $1 == "descendant-branch-depth2" ]]
		then
			Q1=$(./create_tree descendant 2 $i)
		elif [[ $1 == "child-descendant-branch-depth2" ]]
		then
			Q1=$(./create_tree child-descendant 2 $i)
		elif [[ $1 == "child-branch-depth2-wildcard" ]]
		then
			Q1=$(./create_tree child-wildcard 2 $i)
		elif [[ $1 == "descendant-branch-depth2-wildcard" ]]
		then
			Q1=$(./create_tree descendant-wildcard 2 $i)
		elif [[ $1 == "child-descendant-branch-depth2-wildcard" ]]
		then
			Q1=$(./create_tree child-descendant-wildcard 2 $i)
		elif [[ $1 == "child-branch-rank2" ]]
		then
			Q1=$(./create_tree child $i 2)
		elif [[ $1 == "descendant-branch-rank2" ]]
		then
			Q1=$(./create_tree descendant $i 2)
		elif [[ $1 == "child-descendant-branch-rank2" ]]
		then
			Q1=$(./create_tree child-descendant $i 2)
		elif [[ $1 == "child-branch-rank2-wildcard" ]]
		then
			Q1=$(./create_tree child-wildcard $i 2)
		elif [[ $1 == "descendant-branch-rank2-wildcard" ]]
		then
			Q1=$(./create_tree descendant-wildcard $i 2)
		elif [[ $1 == "child-descendant-branch-rank2-wildcard" ]]
		then
			Q1=$(./create_tree child-descendant-wildcard $i 2)
		else
			echo "FATAL ERROR: UNKNOWN TEST ENTERED!!!!!!!!!!!!!!!!!!!!!!!!"
			exit
		fi

		echo -e "\t"$i"\t"$(./benchmark_algorithm canonical "$Q1" "$Q1")"\t"$(./benchmark_algorithm homomorphism "$Q1" "$Q1")";" >> Results/Algorithms/src/$2.m
		echo -en " $i"
	done

	echo "];" >> Results/Algorithms/src/$2.m
	echo >> Results/Algorithms/src/$2.m
	echo "hold on" >> Results/Algorithms/src/$2.m
	echo "f = plot(A(:,1), A(:,2), 'k-o');" >> Results/Algorithms/src/$2.m
	echo "f = plot(A(:,1), A(:,3), 'k-*');" >> Results/Algorithms/src/$2.m
	echo "hold off" >> Results/Algorithms/src/$2.m
	echo "xlabel('Query Size')" >> Results/Algorithms/src/$2.m
	echo "ylabel('Run Time')" >> Results/Algorithms/src/$2.m
	echo "legend('The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')" >> Results/Algorithms/src/$2.m
	echo "saveas(f, '../img/$2.png');" >> Results/Algorithms/src/$2.m

	echo
}

MONDIALARRAY[0]="mondial"
MONDIALARRAY[1]="country"
MONDIALARRAY[2]="province"
MONDIALARRAY[3]="city"
MONDIALARRAY[4]="name"

# Arguments:
#  - $1 = test
#  - $2 = filename
#  - $3 = Query Size
function database_test {
	echo "format long" > Results/Database/src/$2.m
	echo "A = [" >> Results/Database/src/$2.m

	for i in $(seq 0 $3)
	do
		if [[ $1 == "child" ]]
		then
			Q1=$(
				echo -en "/mondial"
				for j in $(seq 1 $i)
				do
					echo -en "/"${MONDIALARRAY[$j]}
				done
			)
		elif [[ $1 == "descendant" ]]
		then
			Q1=$(
				echo -en "/mondial"
				for j in $(seq 1 $i)
				do
					echo -en "//"${MONDIALARRAY[$j]}
				done
			)
		elif [[ $1 == "child-descendant" ]]
		then
			Q1=$(
				echo -en "/mondial"
				for j in $(seq 1 $i)
				do
					if [[ $(($j & 1)) -eq 0 ]]
					then
						echo -en "/"${MONDIALARRAY[$j]}
					else
						echo -en "//"${MONDIALARRAY[$j]}
					fi
				done
			)
		elif [[ $1 == "child-wildcard" ]]
		then
			Q1=$(
				echo -en "/mondial"
				for j in $(seq 1 $i)
				do
					echo -en "/*"
				done
			)
		elif [[ $1 == "descendant-wildcard" ]]
		then
			Q1=$(
				echo -en "/mondial"
				for j in $(seq 1 $i)
				do
					echo -en "//*"
				done
			)
		elif [[ $1 == "child-descendant-wildcard" ]]
		then
			Q1=$(
				echo -en "/mondial"
				for j in $(seq 1 $i)
				do
					if [[ $(($j & 1)) -eq 0 ]]
					then
						echo -en "/*"
					else
						echo -en "//*"
					fi
				done
			)
		elif [[ $1 == "child-branch-depth2" ]]
		then
			if [[ $i -eq 0 ]]
			then
				Q1="/mondial"
			elif [[ $i -eq 1 ]]
			then
				Q1="/mondial[/country[/province]]"
			elif [[ $i -eq 2 ]]
			then
				Q1="/mondial[/country[/province][/province]][/country[/province][/province]]"
			elif [[ $i -eq 3 ]]
			then
				Q1="/mondial[/country[/province][/province][/province]][/country[/province][/province][/province]][/country[/province][/province][/province]]"
			elif [[ $i -eq 4 ]]
			then
				Q1="/mondial[/country[/province][/province][/province][/province]][/country[/province][/province][/province][/province]][/country[/province][/province][/province][/province]][/country[/province][/province][/province][/province]]"
			fi
		elif [[ $1 == "descendant-branch-depth2" ]]
		then
			if [[ $i -eq 0 ]]
			then
				Q1="/mondial"
			elif [[ $i -eq 1 ]]
			then
				Q1="/mondial[//country[//province]]"
			elif [[ $i -eq 2 ]]
			then
				Q1="/mondial[//country[//province][//province]][//country[//province][//province]]"
			elif [[ $i -eq 3 ]]
			then
				Q1="/mondial[//country[//province][//province][//province]][//country[//province][//province][//province]][//country[//province][//province][//province]]"
			elif [[ $i -eq 4 ]]
			then
				Q1="/mondial[//country[//province][//province][//province][//province]][//country[//province][//province][//province][//province]][//country[//province][//province][//province][//province]][//country[//province][//province][//province][//province]]"
			fi
		elif [[ $1 == "child-descendant-branch-depth2" ]]
		then
			if [[ $i -eq 0 ]]
			then
				Q1="/mondial"
			elif [[ $i -eq 1 ]]
			then
				Q1="/mondial[//country[/province]]"
			elif [[ $i -eq 2 ]]
			then
				Q1="/mondial[//country[/province][//province]][/country[//province][/province]]"
			elif [[ $i -eq 3 ]]
			then
				Q1="/mondial[//country[/province][//province][/province]][//country[/province][//province][/province]][//country[/province][//province][/province]]"
			elif [[ $i -eq 4 ]]
			then
				Q1="/mondial[//country[/province][//province][/province][//province]][/country[//province][/province][//province][/province]][//country[/province][//province][/province][//province]][/country[//province][/province][//province][/province]]"
			fi
		elif [[ $1 == "child-branch-depth2-wildcard" ]]
		then
			if [[ $i -eq 0 ]]
			then
				Q1="/mondial"
			elif [[ $i -eq 1 ]]
			then
				Q1="/mondial[/*[/*]]"
			elif [[ $i -eq 2 ]]
			then
				Q1="/mondial[/*[/*][/*]][/*[/*][/*]]"
			elif [[ $i -eq 3 ]]
			then
				Q1="/mondial[/*[/*][/*][/*]][/*[/*][/*][/*]][/*[/*][/*][/*]]"
			elif [[ $i -eq 4 ]]
			then
				Q1="/mondial[/*[/*][/*][/*][/*]][/*[/*][/*][/*][/*]][/*[/*][/*][/*][/*]][/*[/*][/*][/*][/*]]"
			fi
		elif [[ $1 == "descendant-branch-depth2-wildcard" ]]
		then
			if [[ $i -eq 0 ]]
			then
				Q1="/mondial"
			elif [[ $i -eq 1 ]]
			then
				Q1="/mondial[//*[//*]]"
			elif [[ $i -eq 2 ]]
			then
				Q1="/mondial[//*[//*][//*]][//*[//*][//*]]"
			elif [[ $i -eq 3 ]]
			then
				Q1="/mondial[//*[//*][//*][//*]][//*[//*][//*][//*]][//*[//*][//*][//*]]"
			elif [[ $i -eq 4 ]]
			then
				Q1="/mondial[//*[//*][//*][//*][//*]][//*[//*][//*][//*][//*]][//*[//*][//*][//*][//*]][//*[//*][//*][//*][//*]]"
			fi
		elif [[ $1 == "child-descendant-branch-depth2-wildcard" ]]
		then
			if [[ $i -eq 0 ]]
			then
				Q1="/mondial"
			elif [[ $i -eq 1 ]]
			then
				Q1="/mondial[//*[/*]]"
			elif [[ $i -eq 2 ]]
			then
				Q1="/mondial[//*[/*][//*]][/*[//*][/*]]"
			elif [[ $i -eq 3 ]]
			then
				Q1="/mondial[//*[/*][//*][/*]][//*[/*][//*][/*]][//*[/*][//*][/*]]"
			elif [[ $i -eq 4 ]]
			then
				Q1="/mondial[//*[/*][//*][/*][//*]][/*[//*][/*][//*][/*]][//*[/*][//*][/*][//*]][/*[//*][/*][//*][/*]]"
			fi
		elif [[ $1 == "child-branch-rank2" ]]
		then
			if [[ $i -eq 0 ]]
			then
				Q1="/mondial"
			elif [[ $i -eq 1 ]]
			then
				Q1="/mondial[/country][/country]"
			elif [[ $i -eq 2 ]]
			then
				Q1="/mondial[/country[/province][/province]][/country[/province][/province]]"
			elif [[ $i -eq 3 ]]
			then
				Q1="/mondial[/country[/province[/city][/city]][/province[/city][/city]]][/country[/province[/city][/city]][/province[/city][/city]]]"
			elif [[ $i -eq 4 ]]
			then
				Q1="/mondial[/country[/province[/city[/name][/name]][/city[/name][/name]]][/province[/city[/name][/name]][/city[/name][/name]]]][/country[/province[/city[/name][/name]][/city[/name][/name]]][/province[/city[/name][/name]][/city[/name][/name]]]]"
			fi
		elif [[ $1 == "descendant-branch-rank2" ]]
		then
			if [[ $i -eq 0 ]]
			then
				Q1="/mondial"
			elif [[ $i -eq 1 ]]
			then
				Q1="/mondial[//country][//country]"
			elif [[ $i -eq 2 ]]
			then
				Q1="/mondial[//country[//province][//province]][//country[//province][//province]]"
			elif [[ $i -eq 3 ]]
			then
				Q1="/mondial[//country[//province[//city][//city]][//province[//city][//city]]][//country[//province[//city][//city]][//province[//city][//city]]]"
			elif [[ $i -eq 4 ]]
			then
				Q1="/mondial[//country[//province[//city[//name][//name]][//city[//name][//name]]][//province[//city[//name][//name]][//city[//name][//name]]]][//country[//province[//city[//name][//name]][//city[//name][//name]]][//province[//city[//name][//name]][//city[//name][//name]]]]"
			fi
		elif [[ $1 == "child-descendant-branch-rank2" ]]
		then
			if [[ $i -eq 0 ]]
			then
				Q1="/mondial"
			elif [[ $i -eq 1 ]]
			then
				Q1="/mondial[//country][/country]"
			elif [[ $i -eq 2 ]]
			then
				Q1="/mondial[//country[/province][//province]][/country[//province][/province]]"
			elif [[ $i -eq 3 ]]
			then
				Q1="/mondial[//country[/province[//city][/city]][//province[/city][//city]]][//country[/province[//city][/city]][//province[/city][//city]]]"
			elif [[ $i -eq 4 ]]
			then
				Q1="/mondial[//country[/province[//city[/name][//name]][/city[//name][//name]]][/province[//city[/name][//name]][/city[//name][/name]]]][//country[/province[//city[/name][//name]][/city[//name][/name]]][//province[/city[//name][/name]][//city[/name][//name]]]]"
			fi
		elif [[ $1 == "child-branch-rank2-wildcard" ]]
		then
			if [[ $i -eq 0 ]]
			then
				Q1="/mondial"
			elif [[ $i -eq 1 ]]
			then
				Q1="/mondial[/*][/*]"
			elif [[ $i -eq 2 ]]
			then
				Q1="/mondial[/*[/*][/*]][/*[/*][/*]]"
			elif [[ $i -eq 3 ]]
			then
				Q1="/mondial[/*[/*[/*][/*]][/*[/*][/*]]][/*[/*[/*][/*]][/*[/*][/*]]]"
			elif [[ $i -eq 4 ]]
			then
				Q1="/mondial[/*[/*[/*[/*][/*]][/*[/*][/*]]][/*[/*[/*][/*]][/*[/*][/*]]]][/*[/*[/*[/*][/*]][/*[/*][/*]]][/*[/*[/*][/*]][/*[/*][/*]]]]"
			fi
		elif [[ $1 == "descendant-branch-rank2-wildcard" ]]
		then
			if [[ $i -eq 0 ]]
			then
				Q1="/mondial"
			elif [[ $i -eq 1 ]]
			then
				Q1="/mondial[//*][//*]"
			elif [[ $i -eq 2 ]]
			then
				Q1="/mondial[//*[//*][//*]][//*[//*][//*]]"
			elif [[ $i -eq 3 ]]
			then
				Q1="/mondial[//*[//*[//*][//*]][//*[//*][//*]]][//*[//*[//*][//*]][//*[//*][//*]]]"
			elif [[ $i -eq 4 ]]
			then
				Q1="/mondial[//*[//*[//*[//*][//*]][//*[//*][//*]]][//*[//*[//*][//*]][//*[//*][//*]]]][//*[//*[//*[//*][//*]][//*[//*][//*]]][//*[//*[//*][//*]][//*[//*][//*]]]]"
			fi
		elif [[ $1 == "child-descendant-branch-rank2-wildcard" ]]
		then
			if [[ $i -eq 0 ]]
			then
				Q1="/mondial"
			elif [[ $i -eq 1 ]]
			then
				Q1="/mondial[//*][/*]"
			elif [[ $i -eq 2 ]]
			then
				Q1="/mondial[//*[/*][//*]][/*[//*][/*]]"
			elif [[ $i -eq 3 ]]
			then
				Q1="/mondial[//*[/*[//*][/*]][//*[/*][//*]]][/*[//*[/*][//*]][/*[//*][/*]]]"
			elif [[ $i -eq 4 ]]
			then
				Q1="/mondial[//*[/*[//*[/*][//*]][/*[//*][/*]]][//*[/*[//*][/*]][//*[/*][//*]]]][/*[//*[/*[//*][/*]][//*[/*][//*]]][/*[//*[/*][//*]][/*[//*][/*]]]]"
			fi
		else
			echo "FATAL ERROR: UNKNOWN TEST ENTERED!!!!!!!!!!!!!!!!!!!!!!!!"
			exit
		fi

		echo -e "\t"$i"\t"$(./benchmark_database none mondial.xml "$Q1" "$Q1")"\t"$(./benchmark_database canonical mondial.xml "$Q1" "$Q1")"\t"$(./benchmark_database homomorphism mondial.xml "$Q1" "$Q1")";" >> Results/Database/src/$2.m
		echo -en " $i"
	done

	echo "];" >> Results/Database/src/$2.m
	echo >> Results/Database/src/$2.m
	echo "hold on" >> Results/Database/src/$2.m
	echo "f = plot(A(:,1), A(:,2), 'k-x');" >> Results/Database/src/$2.m
	echo "f = plot(A(:,1), A(:,3), 'k-o');" >> Results/Database/src/$2.m
	echo "f = plot(A(:,1), A(:,4), 'k-*');" >> Results/Database/src/$2.m
	echo "hold off" >> Results/Database/src/$2.m
	echo "xlabel('Query Size')" >> Results/Database/src/$2.m
	echo "ylabel('Run Time')" >> Results/Database/src/$2.m
	echo "legend('None', 'The Canonical Model', 'The Homomorphism Technique', 'Location', 'northwest')" >> Results/Database/src/$2.m
	echo "saveas(f, '../img/$2.png');" >> Results/Database/src/$2.m

	echo
}

echo "Running tests for algorithms (/Results/Algorithms/{src, img})..."
echo " - Running test for XPath(/)..."
algorithm_test "child" "ChildGraph" 10
echo " - Running test for XPath(//)..."
algorithm_test "descendant" "DescendantGraph" 10
echo " - Running test for XPath(/, //)..."
algorithm_test "child-descendant" "ChildDescendantGraph" 10
echo " - Running test for XPath(/, *)..."
algorithm_test "child-wildcard" "ChildWildcardGraph" 10
echo " - Running test for XPath(//, *)..."
algorithm_test "descendant-wildcard" "DescendantWildcardGraph" 10
echo " - Running test for XPath(/, //, *)..."
algorithm_test "child-descendant-wildcard" "ChildDescendantWildcardGraph" 10
echo " - Running test for XPath(/, []) (depth 2)..."
algorithm_test "child-branch-depth2" "ChildBranchDepth2Graph" 10
echo " - Running test for XPath(//, []) (depth 2)..." 
algorithm_test "descendant-branch-depth2" "DescendantBranchDepth2Graph" 3
echo " - Running test for XPath(/, //, []) (depth 2)..."
algorithm_test "child-descendant-branch-depth2" "ChildDescendantBranchDepth2Graph" 4
echo " - Running test for XPath(/, [], *) (depth 2)..."
algorithm_test "child-branch-depth2-wildcard" "ChildBranchDepth2WildcardGraph" 10
echo " - Running test for XPath(//, [], *) (depth 2)..."
algorithm_test "descendant-branch-depth2-wildcard" "DescendantBranchDepth2WildcardGraph" 3
echo " - Running test for XPath(/, //, [], *) (depth 2)..."
algorithm_test "child-descendant-branch-depth2-wildcard" "ChildDescendantBranchDepth2WildcardGraph" 3
echo " - Running test for XPath(/, []) (rank 2)..."
algorithm_test "child-branch-rank2" "ChildBranchRank2Graph" 10
echo " - Running test for XPath(//, []) (rank 2)..."
algorithm_test "descendant-branch-rank2" "DescendantBranchRank2Graph" 2
echo " - Running test for XPath(/, //, []) (rank 2)..."
algorithm_test "child-descendant-branch-rank2" "ChildDescendantBranchRank2Graph" 3
echo " - Running test for XPath(/, [], *) (rank 2)..."
algorithm_test "child-branch-rank2-wildcard" "ChildBranchRank2WildcardGraph" 10
echo " - Running test for XPath(//, [], *) (rank 2)..."
algorithm_test "descendant-branch-rank2-wildcard" "DescendantBranchRank2WildcardGraph" 2
echo " - Running test for XPath(/, //, [], *) (rank 2)..."
algorithm_test "child-descendant-branch-rank2-wildcard" "ChildDescendantBranchRank2WildcardGraph" 2
echo
echo "Running tests for database (/Results/Database/{src, img})..."
echo " - Running test for XPath(/)..."
database_test "child" "ChildGraph" 4
echo " - Running test for XPath(//)..."
database_test "descendant" "DescendantGraph" 4
echo " - Running test for XPath(/, //)..."
database_test "child-descendant" "ChildDescendantGraph" 4
echo " - Running test for XPath(/, *)..."
database_test "child-wildcard" "ChildWildcardGraph" 1
echo " - Running test for XPath(//, *)..."
database_test "descendant-wildcard" "DescendantWildcardGraph" 0
echo " - Running test for XPath(/, //, *)..."
database_test "child-descendant-wildcard" "ChildDescendantWildcardGraph" 0
echo " - Running test for XPath(/, []) (depth 2)..."
database_test "child-branch-depth2" "ChildBranchDepth2Graph" 4
echo " - Running test for XPath(//, []) (depth 2)..."
database_test "descendant-branch-depth2" "DescendantBranchDepth2Graph" 3
echo " - Running test for XPath(/, //, []) (depth 2)..."
database_test "child-descendant-branch-depth2" "ChildDescendantBranchDepth2Graph" 4
echo " - Running test for XPath(/, [], *) (depth 2)..."
database_test "child-branch-depth2-wildcard" "ChildBranchDepth2WildcardGraph" 4
echo " - Running test for XPath(//, [], *) (depth 2)..."
database_test "descendant-branch-depth2-wildcard" "DescendantBranchDepth2WildcardGraph" 3
echo " - Running test for XPath(/, //, [], *) (depth 2)..."
database_test "child-descendant-branch-depth2-wildcard" "ChildDescendantBranchDepth2WildcardGraph" 3
echo " - Running test for XPath(/, []) (rank 2)..."
database_test "child-branch-rank2" "ChildBranchRank2Graph" 4
echo " - Running test for XPath(//, []) (rank 2)..."
database_test "descendant-branch-rank2" "DescendantBranchRank2Graph" 3
echo " - Running test for XPath(/, //, []) (rank 2)..."
database_test "child-descendant-branch-rank2" "ChildDescendantBranchRank2Graph" 3
echo " - Running test for XPath(/, [], *) (rank 2)..."
database_test "child-branch-rank2-wildcard" "ChildBranchRank2WildcardGraph" 4
echo " - Running test for XPath(//, [], *) (rank 2)..."
database_test "descendant-branch-rank2-wildcard" "DescendantBranchRank2WildcardGraph" 3
echo " - Running test for XPath(/, //, [], *) (rank 2)..."
database_test "child-descendant-branch-rank2-wildcard" "ChildDescendantBranchRank2WildcardGraph" 3
echo
echo "DONE!"
