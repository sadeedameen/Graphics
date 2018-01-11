// Menu items
enum MENU_TYPE
{
        MENU_FRONT,
        MENU_SPOT,
        MENU_BACK,
        MENU_BACK_FRONT,
};

// Assign a default value
MENU_TYPE show = MENU_BACK_FRONT;

// Menu handling function declaration
void menu(int);

int main()
{
        // ...

        // Create a menu
        glutCreateMenu(menu);

        // Add menu items
        glutAddMenuEntry("Show Front", MENU_FRONT);
        glutAddMenuEntry("Show Back", MENU_BACK);
        glutAddMenuEntry("Spotlight", MENU_SPOT);
        glutAddMenuEntry("Blend 'em all", MENU_BACK_FRONT);

        // Associate a mouse button with menu
        glutAttachMenu(GLUT_RIGHT_BUTTON);

        // ...

        return;
}

// Menu handling function definition
void menu(int item)
{
        switch (item)
        {
        case MENU_FRONT:
        case MENU_SPOT:
        case MENU_DEPTH:
        case MENU_BACK:
        case MENU_BACK_FRONT:
                {
                        show = (MENU_TYPE) item;
                }
                break;
        default:
                {       /* Nothing */       }
                break;
        }

        glutPostRedisplay();

        return;
}
