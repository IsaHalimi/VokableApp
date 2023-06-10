#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>

using namespace std;

string print_menu() {
    cout << "Vokabletrainer Alb-Ger\n\n";
    cout << "Bitte auswählen; \n";
    cout << "(1) Neue Vokable hinzufügen\n";
    cout << "(2) Vokabletest starten\n";
    string option;
    cin >> option;
    return option;
}

vector<string> loadTextFile(string textFile){
        string str;
        ifstream in(textFile);
        vector<string> newVector;
    //Alle Zeilen lesen
    while (getline(in, str))
    {
        //
        if(str.size() > 0)
            newVector.push_back(str);
    }
    return newVector;
}

void save_vector_to_text_file(string fileName, vector<string>myVector){

    //Vokabeln speichern
        ofstream output_file(fileName);
        ostream_iterator<string> output_iterator(output_file, "\n");
        copy(myVector.begin(), myVector.end(), output_iterator);
}

void ask_word(vector<string> voc_ger, vector<string> voc_alb ){

        cout << "Vokabeltest wird gestartet!\n\n";

        double falsch = 0;
        double richtig = 0;
        int i=0;
        double prozent;
        string userInput;
        string sel_translation;

        while(i < voc_ger.size()) {

        int random = rand() % voc_ger.size();
        string sel_elem = voc_ger[random];
        string sel_translation = voc_alb[random];
        cout << "Bitte übersetze folgendes Wort: " << sel_elem << "\n";

        cin >> userInput;

        if(userInput == sel_translation) {
            richtig++;
            cout << richtig << " Richtig!\n\n";
            
        }else {
            falsch++;
            cout << falsch << " Leider falsch\n\n";
            
        }

        i++;
        }

        cout << richtig << " sind Richtig " << falsch << " sind Falsch\n\n";

        prozent = richtig / (richtig + falsch) * 100;

        cout << "Das sind " << prozent << " % richtig.\n\n";

}


int main() {

    bool repeat1 = true;

    while (repeat1){

    string selection = print_menu();
    
    bool repeat = true;

    //Vokabel hinzufügen
    while(repeat){

    vector<string> voc_ger = loadTextFile("voc_ger");
    vector<string> voc_alb = loadTextFile("voc_alb");


        if(selection == "1") {
            cout << "Welche Vokabel (Deutsch)?\n";
            string ger_word;
            string alb_word;
            cin >> ger_word;
            cout << "Wie lautet die Übersetzung?\n";
            cin >> alb_word;

            //Wörter hinzufügen
            voc_ger.push_back(ger_word);
            voc_alb.push_back(alb_word);
            cout << "Vokable wurde hinzugefügt\n";
            cout << "Hinzugefügte Vokabeln: " << voc_ger.size() << "\n";

            //Deutsche Vokabeln speichern
            save_vector_to_text_file("./voc_ger", voc_ger);
            //Albanische Vokabeln speichern
            save_vector_to_text_file("./voc_alb", voc_alb);


            // Vokabeltest
            } else {
                    ask_word(voc_ger, voc_alb);
 
            }

            cout << "Vokabeln hinzufügen?? [y = ja / n = nein]\n\n";
            char answer;
            cin >> answer;
            repeat = answer == 'y';

        }

        cout << "[y = Neustart / n = Beenden]\n\n";
        char answer1;
        cin >> answer1;
        repeat1 = answer1 == 'y';

    }

    cout << "Danke, Tschüss!\n";

    getchar();
    return 0;
}