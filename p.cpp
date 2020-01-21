#include "preproccesor.h"

using namespace std ;

int main(){

    // Use current time as seed for random generator
    srand(time(0));

    //show that all number of attribute
    cout << "producer make : " << NUM << " number." << endl ;

    // set attribute for make queue
    struct mq_attr attr_c1;
    attr_c1.mq_maxmsg = 1;
    attr_c1.mq_flags = 0;
    attr_c1.mq_curmsgs = 0;
    attr_c1.mq_msgsize = SIZE_C1 ;

    struct mq_attr attr_c2;
    attr_c2.mq_maxmsg = 1;
    attr_c2.mq_flags = 0;
    attr_c2.mq_curmsgs = 0;
    attr_c2.mq_msgsize = SIZE_C2 ;

    //we go to open queue
    mqd_t c1 = mq_open( NAME_1 , O_CREAT | O_RDWR , 0666 , &attr_c1);
    mqd_t c2 = mq_open( NAME_2 , O_CREAT | O_RDWR , 0666 , &attr_c2);

    //check for do not make queue
    if(c1 == -1){
        cout<<"Queue c1 failed ; error number: "<< errno <<endl;
    }

    if(c2 == -1){
        cout<<"Queue c2 failed ; error number: "<< errno <<endl;
    }


    //define two queue for two consumer
    struct my_message_c1 queue_c1  ;
    struct my_message_c2 queue_c2  ;

    //set number of number in c1 and c2
    queue_c1.number_of_number = NUM_1 ;
    queue_c2.number_of_number = NUM_2 ;

    //go to make random number for c1 & c2
    for (int i = 0; i < NUM ; i++) {

        if (i < NUM_1){

            bool b = true ;
            queue_c1.number[i] = rand() % 100;

            queue_c1.flag[i] = 0;
            mq_send(c1, (char *) &queue_c1, sizeof(queue_c1), 0);
            cout << "Producer send (number "<< queue_c1.number[i] << " ) massage for c1" << endl ;

            while(b) {
                mq_receive(c1, (char *) &queue_c1, sizeof(my_message_c1), NULL);


                //check this massage receive from producer of consumer
                if (queue_c1.flag[i] == 1) {
                    b = false ;
                    queue_c1.flag[i] = 0 ;
                    mq_send(c1, (char *) &queue_c1, sizeof(queue_c1), 0);
                } else{
                    mq_send(c1, (char *) &queue_c1, sizeof(queue_c1), 0);
                    //sleep(1);
                }


            }
        }

        if (i < NUM_2){

            bool b = true ;
            queue_c2.number[i] = rand() % 100;

            queue_c2.flag[i] = 0;
            mq_send(c2, (char *) &queue_c2, sizeof(queue_c2), 0);
            cout << "Producer send (number "<< queue_c2.number[i] << " ) massage for c2" << endl ;

            while (b) {

                mq_receive(c2, (char *) &queue_c2, sizeof(my_message_c2), NULL);

                //check this massage receive from producer of consumer
                if (queue_c2.flag[i] == 1) {
                    b = false;
                    queue_c2.flag[i] = 0 ;
                    mq_send(c2, (char *) &queue_c2, sizeof(queue_c1), 0);
                } else{
                    mq_send(c2, (char *) &queue_c2, sizeof(queue_c2), 0);
                    //sleep(1);
                }

            }
        }

    }

    mq_close(c1);
    mq_close(c2);
    
    mq_unlink(NAME_1);
    mq_unlink(NAME_2);
    return 0 ;
}