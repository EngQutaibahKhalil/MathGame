
#include <iostream>
using namespace std;

enum enLevels
{
	Easy = 1,
	Mid = 2,
	hard = 3,
	MixLE = 4,
};

enum enOperationType
{
	Add = 1,
	Sub = 2,
	Mul = 3,
	Div = 4,
	MixOP = 5
};

enum enPassOrFail
{
	Pass = 1,
	Fail = 2

};

enum enRightOrWrong
{
	Right = 1,
	Wrong = 2

};

struct stQuestionResult {
	int TheAnswer = 0;
	int TheCorrectAnswer = 0;
	short QuestionNO = 0;
	short Number1 = 0;
	short Number2 = 0;
	char Opration;
	bool IsRight = 0;

};

struct stGameResults {

	short NumberOfQuestions = 0;
	enLevels QuestoinsLevel;
	enOperationType OperatoinType;
	short RightAnswer = 0;
	short WrongAnswer = 0;
	bool PassOrFail;
	string DidPass = "";

};

void SetScreenColor(bool IsItRight) {
	switch (IsItRight)
	{
	case 1:
		system("color 2F");
		break;
	case 0:
		system("color 4F");
		cout << "\a";
		break;
	default:
		break;
	}
}

string Tabs(short TabsNumber) {

	string t = "";

	for (int i = 0; i <= TabsNumber; i++)
		t += "\t";

	return t;

}

short RandomNumber(int From, int To)
{
	//Function to generate a random number
	short randNum = rand() % (To - From + 1) + From;
	return randNum;
}

string DidPassOrFail(short RightAnswers, short WrongAnswers) {

	if (RightAnswers >= WrongAnswers)
		return  "PASS";
	else return  "FAIL";

}

void PrintFinalResultIs(stGameResults& GameResutlt) {
	string PassFail = DidPassOrFail(GameResutlt.RightAnswer, GameResutlt.WrongAnswer);
	cout << Tabs(2) << "\n__________________________________________________________\n";
	cout << Tabs(2) << "\n \t\t Final Result is: " << PassFail;
	cout << Tabs(2) << "\n__________________________________________________________\n";
	SetScreenColor(PassFail == "PASS");
}

enOperationType ReadQuestionsOperationType() {
	short number = 1;

	do
	{
		cout << "Enter operation type: [1]:Add, [2]:Sub, [3]:Mul [4]:Div, [5]:Mix ?  ";
		cin >> number;
	} while (number < 1 || number >5);
	return (enOperationType)number;
}

enLevels ReadQuestionsLevel() {
	short number = 1;

	do
	{
		cout << "Enter questions level: [1]:Easy, [2]:Med, [3]:Hard [4]:Mix ?  ";
		cin >> number;
	} while (number < 1 || number >4);
	return (enLevels)number;
}

short ReadHowManyQuestionsYouWantToAnswer1To50Number() {

	short number = 0;

	do {

		cout << "How many questions you will answer? 1 to 50 ?  ";
		cin >> number;
	} while (number <= 0 || number > 50);
	return number;
}

enLevels GetMixenLevels() {
	return (enLevels)RandomNumber(1, 4);
}

enLevels GetLevel(short LE) {

	switch (LE)
	{
	case 1:
		return enLevels::Easy;
	case 2:
		return enLevels::Mid;
	case 3:
		return enLevels::hard;
	case 4:
		return GetMixenLevels();

	default:
		break;
	}
}

short NumberByLevels(enLevels level) {

	switch (level)
	{
	case  enLevels::Easy:
		return RandomNumber(1, 20);
	case enLevels::Mid:
		return RandomNumber(1, 100);
	case enLevels::hard:
		return RandomNumber(1, 1000);
	case enLevels::MixLE:
		return NumberByLevels((enLevels)RandomNumber(1, 3));
	default:
		break;
	}
}

char GetOperationType(short OP) {

	switch (OP)
	{
	case  enOperationType::Add:
		return '+';
	case  enOperationType::Sub:
		return '-';
	case  enOperationType::Mul:
		return '*';
	case enOperationType::Div:
		return '/';
	case 5:
		return GetOperationType(RandomNumber(1, 4));
	default:
		break;
	}
}

string arrOPType(short OP) {
	string po[5] = { "Add","Sub","Mul","Div","Mix" };
	return po[OP - 1];
}

string arrLEType(short LE) {
	string po[4] = { "Easy","Med","Hard","Mix" };
	return po[LE - 1];
}

stGameResults FillGameResults(short HowManyQuestions, short RightAnswers, short WrongAnswers, enLevels QuestoinsLevel, enOperationType OperatoinType) {

	stGameResults gameResults;

	gameResults.NumberOfQuestions = HowManyQuestions;
	gameResults.QuestoinsLevel = QuestoinsLevel;
	gameResults.OperatoinType = OperatoinType;
	gameResults.RightAnswer = RightAnswers;
	gameResults.WrongAnswer = WrongAnswers;
	gameResults.DidPass = DidPassOrFail(gameResults.RightAnswer, gameResults.WrongAnswer);

	return gameResults;

}

int TheCorrectAnswerIs(short number1, short number2, char OP) {

	switch (OP)
	{
	case '+':
		return number1 + number2;
	case '-':
		return number1 - number2;
	case '*':
		return number1 * number2;
	case '/':
		return number1 / number2;

	default:
		break;
	}
}

void PrintQuestionResult(stQuestionResult& quesrionResult) {

	quesrionResult.TheCorrectAnswer = TheCorrectAnswerIs(quesrionResult.Number1, quesrionResult.Number2, quesrionResult.Opration);
	if (quesrionResult.TheAnswer == quesrionResult.TheCorrectAnswer)
	{
		quesrionResult.IsRight = 1;
		cout << "Right Answer :-)\n";
		SetScreenColor(quesrionResult.IsRight);
	}
	else
	{
		quesrionResult.IsRight = 0;
		cout << "Wrong Answer :-(\n";
		cout << "The Right Answer is: " << quesrionResult.TheCorrectAnswer << endl;
		SetScreenColor(quesrionResult.IsRight);
	}
}

stGameResults PlayMathGame(enOperationType QuestionsOP, enLevels QuestionsLevel, short HowManyQuestions) {
	stQuestionResult questionResult;

	short RightAnswers = 0, WrongAnswers = 0;

	for (short QuestionNO = 1; QuestionNO <= HowManyQuestions; QuestionNO++) {

		cout << "\nQuestion [ " << QuestionNO << " / " << HowManyQuestions << " ] begins:\n\n";
		questionResult.QuestionNO = QuestionNO;
		questionResult.Number1 = NumberByLevels(QuestionsLevel);
		questionResult.Number2 = NumberByLevels(QuestionsLevel);
		questionResult.Opration = GetOperationType(QuestionsOP);

		cout << questionResult.Number1 << endl;
		cout << questionResult.Number2 << "  " << questionResult.Opration << endl;
		cout << "___________\n";

		cin >> questionResult.TheAnswer;

		PrintQuestionResult(questionResult);

		if (questionResult.IsRight == 1)
			RightAnswers++;
		else if (questionResult.IsRight == 0)
			WrongAnswers++;


	}

	return FillGameResults(HowManyQuestions, RightAnswers, WrongAnswers, QuestionsLevel, QuestionsOP);



}

void ShowFinalGameResult(stGameResults GameResult) {
	cout << endl;
	cout << Tabs(2) << "The Number of Questions is: " << GameResult.NumberOfQuestions << endl;
	cout << Tabs(2) << "The Level of Questions is: " << arrLEType(GameResult.QuestoinsLevel) << endl;
	cout << Tabs(2) << "The Operations of Questions is: " << arrOPType(GameResult.OperatoinType) << endl;
	cout << Tabs(2) << "The Right Answers: " << GameResult.RightAnswer << endl;
	cout << Tabs(2) << "The Wrong Answers: " << GameResult.WrongAnswer << endl;
	cout << endl;

}

void ResetScreen() {
	system("cls");
	system("color 0F");
}

void StartGame() {
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		stGameResults GameResult = PlayMathGame(
			ReadQuestionsOperationType(),
			ReadQuestionsLevel(),
			ReadHowManyQuestionsYouWantToAnswer1To50Number()
		);
		PrintFinalResultIs(GameResult);
		ShowFinalGameResult(GameResult);


		cout << "Do you want to play again? Y/N ?  ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	//
	srand((unsigned)time(NULL));
	//
	StartGame();
	return 0;


}

