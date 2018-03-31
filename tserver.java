import java.net.*;
import java.io.*;
import java.util.*;
class tserver
{
public static void main(String args[])throws Exception
{
ServerSocket s=new ServerSocket(7778);
while(true)
{
System.out.println("Waiting for connection...");
Socket soc=s.accept();
DataOutputStream out=new DataOutputStream(soc.getOutputStream());
out.writeBytes("Server Date: " +(new Date()).toString()+"\n");
out.close();
soc.close();
}
}
}

