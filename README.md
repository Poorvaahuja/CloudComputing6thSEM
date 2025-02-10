# CloudComputing6thSEM
# OUTPUTS
![image](https://github.com/user-attachments/assets/7da1ba8a-998c-4dac-94f8-a7e3b7f8e687)
![image](https://github.com/user-attachments/assets/0d45e66c-bcee-4f0a-a483-bc9eb1abc500)

## Instructions
### **📌 Setting Up GitHub Codespaces for Running a TCP Client-Server Program in C**  

GitHub Codespaces allows you to run and test C programs without installing a compiler on your local machine. Follow the steps below to set up your Codespace and run the TCP-based **client-server** model.  

---

## **🔹 Step 1: Create a New GitHub Codespace**  
1. **Go to GitHub** and open your repository (or create a new one).  
2. **Click the “Code” button** (top right).  
3. **Select the “Codespaces” tab** and click **“Create codespace on main”**.  
   - This will launch a full VS Code environment in your browser.  

---

## **🔹 Step 2: Install the C Compiler in Codespaces**  
By default, GitHub Codespaces comes with **GCC preinstalled**, but you can verify it using:  
```sh
gcc --version
```
If GCC is missing, install it with:  
```sh
sudo apt update && sudo apt install -y build-essential
```

---

## **🔹 Step 3: Write the Server Code (`server.c`)**
Inside your **Codespace**, open the integrated terminal (`Ctrl + ~`) and create the server file:  
```sh
nano server.c
```
Copy and paste the following **TCP server code**:
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    read(new_socket, buffer, 1024);
    printf("Client: %s\n", buffer);

    char *response = "Hello from Server!";
    send(new_socket, response, strlen(response), 0);

    close(new_socket);
    close(server_fd);
    return 0;
}
```
**Save and exit**: Press `Ctrl + X`, then `Y`, and `Enter`.

---

## **🔹 Step 4: Write the Client Code (`client.c`)**
Create the client file:
```sh
nano client.c
```
Copy and paste the **TCP client code**:
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "0.0.0.0", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address");
        return -1;
    }

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        return -1;
    }

    char *message = "Hello from Client!";
    send(sock, message, strlen(message), 0);

    read(sock, buffer, 1024);
    printf("Server: %s\n", buffer);

    close(sock);
    return 0;
}
```
**Save and exit**: Press `Ctrl + X`, then `Y`, and `Enter`.

---

## **🔹 Step 5: Compile the Server and Client**
### **Compile the Server**
```sh
gcc server.c -o server
```
### **Compile the Client**
```sh
gcc client.c -o client
```
If there are **no errors**, you will see no output.

---

## **🔹 Step 6: Run the Server**
In the terminal, run:
```sh
./server
```
You should see:
```
Server listening on port 5000...
```

---

## **🔹 Step 7: Open a New Terminal for the Client**
1. Click on **“+”** in the terminal tab to open a new terminal.  
2. Run the client:  
   ```sh
   ./client
   ```
3. You should see the **server's response**:
   ```
   Server: Hello from Server!
   ```

4. Meanwhile, on the **server’s terminal**, you should see:
   ```
   Client: Hello from Client!
   ```

---

## **🔹 Step 8: Make Sure the Port is Forwarded in Codespaces**
GitHub Codespaces **automatically forwards** ports, but you can manually check:
1. Click on the **“PORTS” tab** (bottom panel).
2. If port **5000** is not listed, click **“Forward a Port”** and enter `5000`.
3. Use the **provided URL** to connect if necessary.

---

## **🔹 Troubleshooting**
### **1️⃣ Error: Address already in use**
If you see:
```
Bind failed: Address already in use
```
Run:
```sh
sudo fuser -k 5000/tcp
```
Then restart the server.

### **2️⃣ Error: Connection refused**
- Make sure the **server is running** before starting the client.
- Use `0.0.0.0` in the `client.c` file if using GitHub Codespaces.

---

## **✅ Final Output**
### **Server Terminal**
```
Server listening on port 5000...
Client: Hello from Client!
```
### **Client Terminal**
```
Server: Hello from Server!
```

---

## **🎯 Summary**
| Step | Action |
|------|--------|
| **1** | Create a GitHub Codespace |
| **2** | Install `gcc` (if not already installed) |
| **3** | Write `server.c` |
| **4** | Write `client.c` |
| **5** | Compile both programs |
| **6** | Run the server (`./server`) |
| **7** | Open a new terminal and run the client (`./client`) |
| **8** | Check port forwarding in Codespaces |

Now your **TCP client-server program** is running successfully on GitHub Codespaces! 🚀 Let me know if you need further help. 🎯
