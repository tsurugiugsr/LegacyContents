package pojo;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class Server implements Runnable {
    @Override
    public void run() {
        try {
            ServerSocket serverSocket = new ServerSocket(6671);
            while (true) {
                System.out.println("等待用户连接：");
                Socket client = serverSocket.accept();  //接受客户端请求
                try {
                    //接受客户端信息
                    BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream()));
                    String str = in.readLine();
                    System.out.println("接收到："+str);
                    String[] deStr = str.split(" ");
                    String sign = deStr[0];
                    if(sign.equals("OC_Register")){
                        NormalUser_Authority.addNormalUser(deStr);
                    }
                    if(sign.equals("OC_Login")){
                        PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(client.getOutputStream())),true);
                        String res = NormalUser_Authority.checkPassword(deStr[1], deStr[2]);
                        out.println(res);
                        out.close();
                    }
                    if(sign.equals("OC_Info")){
                        NormalUser_Info.addNormalUserInfo(deStr);
                    }
                    if(sign.equals("OC_Inquire")){
                        PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(client.getOutputStream())),true);
                        String res = NAT_Info.getNATInfo(deStr[1]);
                        out.println(res);
                        out.close();
                    }
                    if(sign.equals("NATLogin")){
                        PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(client.getOutputStream())),true);
                        String res = NAT_Authority.checkPassword(deStr[1], deStr[2]);
                        out.println(res);
                        out.close();
                    }
                    if(sign.equals("NATSubmit")){
                        NAT_Info.addNATInfo(deStr);
                    }
                    if(sign.equals("VIM_LOGIN")){
                        PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(client.getOutputStream())),true);
                        String res = Vaccine_Authority.checkPassword(deStr[1], deStr[2]);
                        out.println(res);
                        out.close();
                    }
                    if(sign.equals("VIM_ADD")){
                        Vaccine_Info.addVaccineInfo(deStr);
                    }
                    if(sign.equals("VIM_EDIT")){
                        //deStr[1~4]是原来的，deStr[5~8]是新的
                        int id = Vaccine_Info.getOriginalId(deStr);
                        Vaccine_Info.updateVaccineInfo(id, deStr);
                    }
                    if(sign.equals("VIM_QUERY_DATE")){
                        PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(client.getOutputStream())),true);
                        String res = Vaccine_Info.getVaccineInfoByDate(deStr);
                        System.out.println(res);
                        out.println(res);
                        out.close();
                    }
                    if(sign.equals("VIM_DELETE")){
                        Vaccine_Info.deleteVaccineInfo(deStr);
                    }
                    if(sign.equals("AC")){
                        PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(client.getOutputStream())),true);
                        String res = NormalUser_Info.getNormalUserInfo(deStr);
                        out.println(res);
                        out.close();
                    }
                    if(sign.equals("CN")) {
                        PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(client.getOutputStream())), true);
                        String res = Check_Info.checkNatInfo();
                        out.println(res);
                        out.close();
                    }
                    if(sign.equals("VN")) {
                        PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(client.getOutputStream())), true);
                        String res = Vaccine_Info.checkVN();
                        out.println(res);
                        out.close();
                    }
                    in.close();
                } catch (Exception ex) {
                    ex.printStackTrace();
                } finally {
                    client.close();
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        } 
    }

    public static void main(String [] args){
        Thread desktopServerThread = new Thread(new Server());
        desktopServerThread.start();
    }
}
