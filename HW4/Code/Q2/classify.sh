if [ "$#" -ne 4 ]; then
	echo Error: Invalid number of arguments
	echo "e.g. sh classify.sh <trainset filename containing graphs> <active graph IDs filename> <inactive graph IDs filename> <testset filename containing graphs>"
else
	TRAININGFILE=$1
	ACTIVEFILE=$2
	INACTIVEFILE=$3
	TESTINGFILE=$4

	# Make the executable files
	make

	# Convert the file into required format
	./convertFile $TRAININGFILE $ACTIVEFILE $INACTIVEFILE $TESTINGFILE

	# Conversion
	./convertForIso testing.hasit testing.hasito
	./convertForIso training.hasit training.hasito

	# Run FSG for finding subgraphs
	./fsg training.inactive.hasit -s 25
	./fsg training.active.hasit -s 25
	./convertForIso training.active.fp training.active.fpo
	./convertForIso training.inactive.fp training.inactive.fpo

	# Compute distinct features
	java -cp src:GraphLib/Motif/:GraphLib/lib/* Check training.inactive.fpo training.active.fpo > distinguishinFeats
	./distFeat distinguishinFeats training.inactive.fpo training.inactive.fpo_final

	# Repeat the same process with maximal subgraphs
	./fsg training.inactive.hasit -s 25 -x
	./fsg training.active.hasit -s 25 -x
	./convertForIso training.active.fp training.active.fpo
	./convertForIso training.inactive.fp training.inactive.fpo
	java -cp src:GraphLib/Motif/:GraphLib/lib/* Check training.active.fpo training.inactive.fpo > distinguishinFeats
	./distFeat distinguishinFeats training.active.fpo training.active.fpo_final
	cat training.active.fpo_final training.inactive.fpo_final > training.fpo_final

	# Calculate features for training and testing
	java -cp src:GraphLib/Motif/:GraphLib/lib/* CountFeatures training.fpo_final training.hasito training.hasitop > AllFeatures
	java -cp src:GraphLib/Motif/:GraphLib/lib/* CountFeatures training.fpo_final testing.hasito > AllActiveFeatures

	# Print output
	python sk.py > output.txt
fi