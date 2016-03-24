#ifndef PROTOCOLE_H
#define PROTOCOLE_H

#define BUFFER 500
#define VERSION 1


class protocole
{
public:
    struct envoi
    {
        int version;
        unsigned long time;
        char password[20];
        int query;
    };

    struct reponse
    {
        int version;
        unsigned long time;
        int query;
        char message[20];
    };

    static int send_query(char *data, char *password, int query, int *len1);
    static int send_reponse(char *data, char *message, int query, int *len1);

    static int parse_query(char *data, protocole::envoi *envoi_data);
    static int parse_reponse(char *data, protocole::reponse *reponse_data);

    static int test();

};

#endif // PROTOCOLE_H

