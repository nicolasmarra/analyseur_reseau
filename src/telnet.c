#include "telnet.h"


void traiter_telnet(const u_char *paquet, int taille, int verbosite)
{

    printf("\n");
    printf("Telnet\n");

    if(verbosite > 2)
    {
        for(int i = 0; i < taille; i++)
        {
            // Les commandes Telnet sont précédées de 0xFF
            if(paquet[i] == 0xFF && i + 2 < taille)
            {
                printf("> ");
                afficher_commandes_telnet(paquet[i+1]);
                printf(" ");
                afficher_options_telnet(paquet[i+2]);
                printf("\n");
                i+=2;
            }else{
                printf("%c", paquet[i]);
            }
        }

    }
}

void afficher_commandes_telnet(const uint8_t commande)
{
    switch (commande)
    {
    case 0xF0:
        printf("SE");
        break;
    case 0xF1:
        printf("NOP");
        break;
    case 0xF2:
        printf("DM");
        break;
    case 0xF3:
        printf("BRK");
        break;
    case 0xF4:
        printf("IP");
        break;
    case 0xF5:
        printf("AO");
        break;
    case 0xF6:
        printf("AYT");
        break;
    case 0xF7:
        printf("EC");
        break;
    case 0xF8:
        printf("EL");
        break;
    case 0xF9:
        printf("GA");
        break;
    case 0XFA:
        printf("SB");
        break;
    case 0xFB:
        printf("WILL");
        break;
    case 0xFC:
        printf("WONT");
        break;
    case 0xFD:
        printf("DO");
        break;
    case 0xFE:
        printf("DONT");
        break;
    case 0xFF:
        printf("IAC");
        break;
    }
}

void afficher_options_telnet(const uint8_t option)
{
    switch (option)
    {
        case 0x00:
            printf("Binary");
            break;
        case 0x01:
            printf("Echo");
            break;
        case 0x02:
            printf("Reconnection");
            break;
        case 0x03:
            printf("Suppress Go Ahead");
            break;
        case 0x04:
            printf("Approx Message Size Negotiation");
            break;
        case 0x05:
            printf("Status");
            break;
        case 0x06:
            printf("Timing Mark");
            break;
        case 0x07:
            printf("Remote Controlled");
            break;
        case 0x08:
            printf("Output Line Width");
            break;
        case 0x09:
            printf("Output Page Size");
            break;
        case 0x0A:
            printf("Output Carriage-Return Disposition");
            break;
        case 0x0B:
            printf("Output Horizontal Tab Stops");
            break;
        case 0x0C:
            printf("Output Horizontal Tab Disposition");
            break;
        case 0x0D:
            printf("Output Formfeed Disposition");
            break;
        case 0x0E:
            printf("Output Vertical Tabstops");
            break;
        case 0x0F:
            printf("Output Vertical Tab Disposition");
            break;
        case 0x10:
            printf("Output Linefeed Disposition");
            break;
        case 0x11:
            printf("Extended ASCII");
            break;
        case 0x12:
            printf("Logout");
            break;
        case 0x13:
            printf("Byte Macro");
            break;
        case 0x14:
            printf("Data Entry Terminal");
            break;
        case 0x15:
            printf("SUPDUP");
            break;
        case 0x16:
            printf("SUPDUP Output");
            break;
        case 0x17: 
            printf("Send Location");
            break;
        case 0x18:
            printf("Terminal Type");
            break;
        case 0x19:
            printf("End of Record");
            break;
        case 0x1A:
            printf("TACACS User Identification");
            break;
        case 0x1B: 
            printf("Output Marking");
            break;
        case 0x1C:
            printf("Terminal Location Number");
            break;
        case 0x1D:
            printf("Telnet 3270 Regime");
            break;
        case 0x1E:
            printf("X.3 PAD");
            break;  
        case 0x1F:
            printf("Negotiate About Window Size");
            break;
        case 0x20:
            printf("Terminal Speed");
            break;
        case 0x21:
            printf("Remote Flow Control");
            break;
        case 0x22:
            printf("Linemode");
            break;
        case 0x23:
            printf("X Display Location");
            break;
        case 0x24:
            printf("Environment Option");
            break;
        case 0x25:
            printf("Authentication Option");
            break;
        case 0x26:
            printf("Encryption Option");
            break;
        case 0x27:
            printf("New Environment Option");
            break;
        case 0x28: 
            printf("TN3270E");
            break;
        case 0x29:
            printf("XAUTH");
            break;
        case 0x2A: 
            printf("CHARSET");
            break;
        case 0x2B:
            printf("Telnet Remote Serial Port");
            break;
        case 0x2C:
            printf("Com Port Control Option");
            break;
        case 0x2D:
            printf("Telnet Suppress Local Echo");
            break;
        case 0x2E:
            printf("Telnet Start TLS");
            break;
        case 0x2F:
            printf("KERMIT");
            break;
        case 0x30:
            printf("SEND-URL");
            break;
        case 0x31:
            printf("FORWARD_X");
            break;
        case 0x32:
            printf("PRAGMA_LOGON");
            break;
        case 0x33:
            printf("SSPI_LOGON");
            break;
        case 0x34:
            printf("PRAGMA_HEARTBEAT");
            break;
        case 0x35:
            printf("EXOPL");
            break;
        case 0x36:
            printf("GSSAPI");
            break;
        case 0xFF:
            printf("Extended-Options-List");
            break;
        
    }
}