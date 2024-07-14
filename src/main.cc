/*_           _ _           
 | |         (_) |          
 | |__   ___  _| | ___ _ __ 
 | '_ \ / _ \| | |/ _ \ '__|
 | |_) | (_) | | |  __/ |   
 |_.__/ \___/|_|_|\___|_|   
       | |     | |          
  _ __ | | __ _| |_ ___     
 | '_ \| |/ _` | __/ _ \    
 | |_) | | (_| | ||  __/    
 | .__/|_|\__,_|\__\___|    
 | |                        
 |_|____                    
  / ____|_     _            
 | |   _| |_ _| |_          
 | |  |_   _|_   _|         
 | |____|_|   |_|           
  \_____|                   
*/

#include "application.h"
#include "cmd.h"

int main(int argc, char *argv[])
{
    mib::Application app;
    mib::CmdPrint cmdPrint;
    app.add(cmdPrint);
    return app.run(argc, argv);
}