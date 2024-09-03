
utDir=$PWD"../build_debug/ut/"
utApplicationsDir="src/Applications/"
utSolverCoreDir="src/SolverCore/"
utUtilityFunctions="src/UtilityFunctions/"
utSubsystemsDir="src/Subsystems/"
gTestFlags="--gtest_repeat=20 --gtest_shuffle"
gTestSeed="--gtest_random_seed=1020"
utResults="ut_results.txt"
utResultsDir=$PWD"../ut/results/"
outputDir=$PWD"../ut/report/"
# init execution list
testSet=()
# define all tests
testSet+=($utSolverCoreDir"ut_SolverCore")
testSet+=($utUtilityFunctions"ut_UtilityFunctions")
testSet+=($utSubsystemsDir"ut_Subsystems")
testSet+=($utApplicationsDir"ut_applications")
# clear all old files in the report dir
rm -rf $outputDir*
# store the ut result
if [ ! -d $utResultsDir ]; then
    mkdir $utResultsDir
fi
# checkwether ut_result exits
if [ -f $utResultsDir$utResults ]; then
    echo "$utResults exits. removing..."
    rm $utResultsDir$utResults
fi
touch $utResultsDir$utResults
# then run all tests
for testName in "${testSet[@]}"
do
$"$utDir$testName" --gtest_brief=1 $gTestFlags $gTestSeed --gtest_output=xml:$outputDir$testName >> $utResultsDir$utResults
done

./ut_scan.sh $utResultsDir$utResults
finalResults=$?
exit $finalResults