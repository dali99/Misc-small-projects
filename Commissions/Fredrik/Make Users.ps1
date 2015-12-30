############################################
## Script by Daniel Løvbrøtte Olsen, 1ELA ##
## For Fredrik Refstie                    ##
############################################
#Imports a comma separated file, COMMA SEPARATED NOT SEMI;COLON
$Users = Import-Csv .\Users.csv
#Loops through each of the rows, or objects really.
forEach ($User in $Users)
{
    $firstname = $User.first
    #Select two first of first name and store it in $first
    $first = $firstname[0..1]
    $lastname = $User.last
    #Select three first of lastname and store it in $last
    $last = $lastname[0..2]
    #Merge the two things
    $username = "$first$last"
    #Hack to fix weird spaces between characters
    $username = $username -replace " ", ""
    #Write the command to a batfile to run in a normal cmd window
    "dsadd user `"cn=$username, ou=Illuminati, dc=datavg2, dc=local`" -fn $firstname -ln $lastname -pwd Admin123" | out-file run.bat -Encoding "UTF8" -Append
}
"echo Script has  finished running, thanks based Daniel in 1ELA for making our lives easier" | out-file run.bat -Encoding "UTF8" -Append
"PAUSE" | out-file run.bat -Encoding "UTF8" -append
#Turn off safeties
"@ECHO OFF" | out-file run.bat -Encoding "UTF8" -append
#Delete yourself
"DEL `"%~f0`"" | out-file run.bat -Encoding "UTF8" -append
#Start the batfile you just created
Start-Process "cmd.exe" "/c run.bat"
