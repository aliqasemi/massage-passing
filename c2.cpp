#include "preproccesor.h"

using namespace std ;

int main(){

    sleep(1.5);

    //we go to open queue
    mqd_t c2 = mq_open(NAME_2, O_RDWR);

    if(c2 == -1){
        cout<<"Queue failed ; error number: "<<errno<<endl;
    }

    //define one queue for  consumer1
    struct my_message_c2 queue_c2 ;


    //make boolean attribute for show number of c2
    bool firstCycle = true;

    //go to get number from producer and sent accept massage
    for (int i = 0; i < NUM_2 ; i++) {

        bool b = true ;
        mq_receive(c2, (char *) &queue_c2, sizeof(my_message_c2), NULL);

        //make boolean attribute for check  the massage reach or no reach
        while (b) {

            if (i == 0 && firstCycle) {
                cout << "Consumer c2 has :" << queue_c2.number_of_number << " number" << endl;
                firstCycle = false;
            }

            if(queue_c2.flag[i] == 0) {
                cout << "Consumer c2 get number : " << queue_c2.number[i] << " from producer." << endl;
            }

            queue_c2.flag[i] = 1;

            mq_send(c2, (char *) &queue_c2, sizeof(queue_c2), 0);

            //sleep(2);

            mq_receive(c2, (char *) &queue_c2, sizeof(my_message_c2), NULL);

            //if i is the end of loop ; c2 is sleep for always ; so i break after my self debugging
            if(i == NUM_2 - 1 ){
                break ;
            }

            if (queue_c2.flag[i] == 1){
                b = true ;
            } else{
                b = false ;
            }
        }
    }

    mq_close(c2);
    return 0 ;
}