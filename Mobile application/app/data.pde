import java.io.*;

import java.util.ArrayList; //<>//


final String My_Profile = "image/My Profile.png";
final String Login = "image/Login/Login.png";
final String Forget_password = "image/Login/Forget password.png";
final String Register = "image/Login/Register.png";
final String Term_and_condition = "image/Login/Term and condition.png";
final String My_pets = "image/My pets/My pets.png";
final String New_pets = "image/My pets/New pets.png";
final String Main = "image/My pets/Main/Main.png";
final String GPS = "image/My pets/Main/GPS.png";
final String Society = "image/My pets/Main/Society.png";
final String Health = "image/My pets/Main/Health/Health.png";
final String Pet_condition = "image/My pets/Main/Health/Pet condition.png";
final String Posture = "image/My pets/Main/Health/posture.png";
final String Hosiptal = "image/My pets/Main/Health/hosiptal/hosiptal.png";
final String Hosiptal1 = "image/My pets/Main/Health/hosiptal/hosiptal1.png";

private class Database {
    int max_data = 10;
    JSONObject[] data = new JSONObject[max_data];
    Database() {}
}

void refreshData() {
    File dir;
    File[] files;
    dir = new File(dataPath(""));
    files = dir.listFiles();
    JSONObject json;
    for (int i = 0; i <= files.length - 1; i++) {
        String path = files[i].getAbsolutePath();
        if (path.toLowerCase().endsWith(".json")) {
            json = loadJSONObject(path);
            if (json != null) {
                db.data[i] = json;
            }
        }
    }
}

public class AllData {
    Boolean checkPassword(String name, String password) {
        for (JSONObject datas: db.data) {
            if (datas != null) {
              String datatype = (String)datas.get("data_type");
                if (datatype.equals("user_info")) {
                  JSONObject userinfo =  (JSONObject) datas.get("info");
                  String username = (String)userinfo.get("username");
                  String passwords = (String)userinfo.get("password");
                  if(username.equals(name)&&passwords.equals(password)){
                    machinecode = (String)userinfo.get("machinecode");
                    return true;
                  }                    
                }
            }
        }
        return false;
    }
    

    
    int getPetsByMachine(String machinecode){
      int pet = -1;
       for (JSONObject datas: db.data) {
            if (datas != null) {
              String datatype = datas.getString("data_type");
                if (datatype.equals("pets_machine")) {
                  JSONObject pminfo =  (JSONObject) datas.get("info");
                  String data_machinecode = pminfo.getString("machine");
                  if(data_machinecode.equals(machinecode)){
                    pet =(int) pminfo.get("petId");
                  }
                  
                }
            }
       }
      return pet;
    }
    
    JSONObject getPetDetailByID(String id){
      JSONObject detail = new JSONObject();
       for (JSONObject datas: db.data) {
            if (datas != null) {
              String datatype = datas.getString("data_type");
                if (datatype.equals("pets_detail")) {
                  JSONObject details = (JSONObject) datas.get("info");
                  String petId = details.getString("petId");
                  if(petId.equals(id)){
                    detail = datas;
                  }
                }
            }
       }
       return detail;
    }
    
        void userRegister(int id, String firstname,String lastname,String email,String password){
      String fullPath = "data"+ File.separator + "user_info" + id+ ".json";
           try{
                     File file = new File(fullPath);      
                   if (!file.getParentFile().exists()){
                        file.getParentFile().mkdirs();       
                      }      
                    if (file.exists()) {
                        file.delete();       
                      }      
                      file.createNewFile();
                      JSONObject root =new JSONObject();
                      root.put("data_type","user_info");
                      JSONArray array=new JSONArray();
                      JSONObject info=new JSONObject();
                      info.put("username",firstname.concat(lastname));
                      info.put("password",password);
                      info.put("machine",id);
                      array.setJSONObject(1,info);
                      root.put("info",array);
                       Writer write = new OutputStreamWriter(new FileOutputStream(file), "UTF-8");      
                       write.write(root.toString());      
                       write.flush();      
                       write.close();
        }
         catch(Exception e) {
            e.printStackTrace();

     }
    }
    
     JSONObject getPetInfoByID(String id){
      JSONObject detail = new JSONObject();
       for (JSONObject datas: db.data) {
            if (datas != null) {
              String datatype = datas.getString("data_type");
                if (datatype.equals("pets_info")) {
                  JSONObject details = (JSONObject) datas.get("info");
                  String petId = details.getString("petId");
                  if(petId.equals(id)){
                    detail = datas;
                  }
                }
            }
       }
       return detail;
    }
}


