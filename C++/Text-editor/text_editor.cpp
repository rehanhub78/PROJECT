#include<iostream>
#include<stack>
using namespace std;
class Command{
    public:
        virtual ~Command(){};
        virtual void execute() = 0;
        virtual void undo() = 0;
};

class Document{
    private:
        string document;
    public:
        void insert(int idx,const string& info){
            document.insert(idx,info);
        }
        void remove(int idx,int length){
            document.erase(idx, length);
        }
        void display(){
            cout << document<<endl;
        }
};

class InsertCommand : public Command{
    private:
        Document* doc;
        int idx;
        string text;
    public:
        InsertCommand(Document* a,int b,string c){
            doc = a;
            idx = b;
            text = c;
        }
        void execute(){
            doc->insert(idx, text);
        }
        void undo(){
            doc->remove(idx, text.length());
        }
};

class DeleteCommand : public Command{
    private:
        Document* doc;
        int idx;
        string text;
        DeleteCommand(Document* a,int b,string c){
            doc = a;
            idx = b;
            text = c;
        }
        void execute(){
            doc->remove(idx, text.length());
        }
        void undo(){
            doc->insert(idx, text);
        }
};

class TextEditor{
    private:
        Document mydoc;
        stack<Command*> undoStack;
        stack<Command*> redoStack;
    public:
        void executeCommand(Command* cmd){
            cmd->execute();
            undoStack.push(cmd);
            while(!redoStack.empty()){
                delete redoStack.top();
                redoStack.pop();
            }
        }
        void undo(){
            if(undoStack.empty()){
                return;
            }
            Command* cmd = undoStack.top();
            undoStack.pop();
            cmd->undo();
            redoStack.push(cmd);
        }
        void redo(){
            if(redoStack.empty()){
                return;
            }
            Command* cmd = redoStack.top();
            redoStack.pop();
            cmd->execute();
            undoStack.push(cmd);
        }
        void showDocument(){
            mydoc.display();
        }
        Document* getDocument(){
            return &mydoc;
        }
};

int main(){
    TextEditor obj1;
    Document* docptr = obj1.getDocument();
    
    cout<<" -----Starting Editor-----"<<endl;
    Command* cmd1 = new InsertCommand(docptr,0 ,"Hello");
    obj1.executeCommand(cmd1);
    cout<<"After inserting 'Hello' : ";
    obj1.showDocument();

    Command* cmd2 = new InsertCommand(docptr,5 ," World");
    obj1.executeCommand(cmd2);
    cout<<"After inserting 'World' : ";
    obj1.showDocument();
}