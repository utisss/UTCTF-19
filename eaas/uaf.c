#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRINGS 20

int user_id;

char *key = "5F45246490B1F70265F07D415CD57925F19BB84322C982AEAB512884B318A36D6450760E5EF8162DB2351DA54E74259F11601D2FCCC6468F67B771F88F691524";


struct info {
    char *plaintext; char *encrypt;
    void (*encrypt_text)(char *plaintext, char *encrypt);
    void (*print_encryption)();
    int dirty;
    unsigned int len;
};

struct info *information[MAX_STRINGS];
void print_key() {
    printf("OTP Encryption\n");
}

void print_xor() {
    printf("XOR Encryption\n");
}

void key_encrypt(char *plaintext, char *encrypt) {
    //get fucked kid
    size_t len = strlen(encrypt);
    size_t key_len = strlen(key);
    for(int i = 0; i < len; ++i) {
        int key_index = i % key_len;
        encrypt[i] ^= key[key_index];
    }
    encrypt[len] = '\x00';
}

void xor_encrypt(char *plaintext, char *encrypt) {
    char xor = (char)user_id;
    //get fucked kid
   size_t len = strlen(encrypt);
    for(int i = 0; i < len; ++i) {
        encrypt[i] = plaintext[i] ^ xor;
    }
    encrypt[len] = '\x00';
}

void edit_encrypted_message() {
    printf("Enter the index of the message that you wish to edit\n");
    int index;
    scanf("%d%*c", &index);
    if(index < 0 || index >= MAX_STRINGS || information[index] == NULL) {
        printf("Invalid index\n");
        return;
    }
    char *plaintext = information[index]->plaintext;
    char *ciphertext = information[index]->encrypt;
    printf("Enter the new message\n");
    fgets(plaintext, information[index]->len, stdin);
    information[index]->encrypt_text(plaintext, ciphertext);
}

void print_menu() {
    printf("Welcome to Encryption as a Service!\n What would you like to do?\n");
    printf("1. Encrypt message\n");
    printf("2. Remove Encrypted Message\n");
    printf("3. View Encrypted Message\n");
    printf("4. Edit Encrypted Message\n");
    printf("5. Exit\n");
    printf(">");
}

void print_encryption_menu() {
    printf("Choose an encryption option:\n");
    printf("1. OTP\n");
    printf("2. XOR\n");
    printf(">");
}


int find_index() {
    for(int i = 0; i < MAX_STRINGS; ++i) {
        if(information[i] == NULL || information[i]->dirty) {
            return i;
        }
    }
    return -1;
}

struct info *create_info() {
    int index = find_index();
    if(index == -1) {
        printf("You've reached the maximum number of messages that you can store.\n");
        return NULL;
    }

    if(information[index] == NULL) {
        information[index] = malloc(sizeof(struct info));
    }
    information[index]->dirty = 0;
    return information[index];
}

void view_messages() {
    for(int i = 0; i < MAX_STRINGS; ++i) {
        if(information[i] != NULL && !information[i]->dirty) {
            printf("Message #%d\n", i);
            information[i]->print_encryption();
            printf("Plaintext: %s\n", information[i]->plaintext);
            printf("Ciphertext: %s\n", information[i]->encrypt);
        }
    }
}

void encrypt_string() {
    print_encryption_menu();
    int choice;
    scanf("%d%*c", &choice);
    struct info *info = create_info();
    if(info == NULL) {
        return;
    }

    switch(choice) {
        case 1:
            info->encrypt_text = &key_encrypt;
            info->print_encryption = &print_key;
            break;
        case 2:
            info->encrypt_text = &xor_encrypt;
            info->print_encryption = &print_xor;
            break;
        default:
            printf("Not a valid choice\n");
            return;
    }

    printf("How long is your message?\n>");
    unsigned int length;
    scanf("%d%*c", &length);
    ++length;
    info->len = length;
    char *plaintext = malloc(length);
    printf("Please enter your message: ");
    fgets(plaintext, length, stdin);
    info->plaintext = plaintext;
    char *encrypt = malloc(length);
    info->encrypt = encrypt;
    info->encrypt_text(plaintext, encrypt);
    printf("Your encrypted message is: %s\n", encrypt);
}

void remove_encrypted_string() {
    int choice;
    printf("Enter the index of the message that you want to remove: ");
    scanf("%d%*c", &choice);
    if(choice < 0 || choice >= MAX_STRINGS || information[choice] == NULL || information[choice]->dirty == 1) {
        printf("Not a valid index.\n");
        return;
    }
    information[choice]->dirty = 1;
    free(information[choice]->plaintext);
    free(information[choice]->encrypt);
}

int main(int argc, char **argv) {
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    printf("What is your user id?\n");

    scanf("%d%*c", &user_id);
    while(1) {
        print_menu();
        int choice;
        scanf("%d%*c", &choice);
        switch(choice) {
            case 1:
                encrypt_string();
                break;
            case 2:
                remove_encrypted_string();
                break;
            case 3:
                view_messages();
                break;
            case 4:
                edit_encrypted_message();
                break;
            case 5:
                return 0;
            default:
                printf("Not a valid option\n");
        }
    }
    
    return 0;
}
