# NetPractice
> Learn about TCP/IP 

## Table of Contents
* [General Info](#general-information)
* [Network range and Mask](#network-range-and-mask)
* [Levels](#levels)
* [Project Status](#project-status)
* [Contact](#contact)

## General Information
- For this project we have different type of infrastructure  
and we had to connect two interface between them or/and on the net etc.
- Check the link here to see all the [levels](#levels)

## Network range and Mask

#### **When the Mask is easy, which means it ends with 0 we have:**
- The subnet number that is equal to 0
- The first host Ip adress equal to the subnet + 1
- The broadcast adress equal to 255 
- The last host Ip adress equal to the broadcast - 1

| Octets | 1 | 2 | 3 | 4 |
| -|-|-|-|-|
| Adress | 192 | 169 | 12 | 234 |
| Mask | 255 | 255 | 255 | 0 |
| Subnet | 192 | 169 | 12 | 0 |
| First | 192 | 169 | 12 | 1 |
| Broadcast | 192 | 169 | 12 | 255 |
| Last | 192 | 169 | 12 | 254 |

Therefore the range of Ip address that are usable is from `192.169.12.1` to `192.169.12.254`

With the same logic if the Mask would have been `255.255.0.0` the range of usable host Ip address would have been from `192.169.0.1` to `192.169.255.254`.

#### **For the rest of the masks**
If we take `255.255.255.128` as a Mask and `192.169.12.234` as on Ip adress in the range.

We then need to perform a `Binary AND` operation.

Every address converted to binary:  
| Octets | 1 | 2 | 3 | 4 |
|-|-|-|-|-|
| Ip address | 11000000 | 10101001 | 00001100 | 11101010 |
| Mask | 11111111 | 11111111 | 11111111 | 100000000 |
| AND | 11000000 | 10101001 | 00001100 | 10000000 |
| Subnet | 192 | 169 | 12 | 128 |
| First | 192 | 169 | 12 | 129 |
| Broadcast | 192 | 169 | 12 | 255 |
| Last | 192 | 169 | 12 | 254 |

- The subnet is find using an Binary AND operation with the Mask and the Ip address and convert it back.  
- The first is the subnet + 1
- The broadcast is the subnet + 256 - 128 (the mask) - 1. Soit 128 + 256 - 128 - 1 = `255`
- The last Ip is the broadcast + 1

Therefore the range of Ip address that are usable is from `192.169.12.129` to `192.169.12.254`

## Levels
In the first level, we had to make comunication between two client in the same network.

![Level one](./img/level1.png)

<details>
<summary>How to resolve level 1 ?</summary>

- Goal 1:  
We have to change the Interface A1 IP address to be between `104.96.23.1` and `104.96.23.254`. [Learn how](#network-range-and-mask) to get the range.

- Goal 2:  
We have to change the Interface D1 IP address to be between `211.191.0.1` and `211.191.255.254`. [Learn how](#network-range-and-mask) to get the range.

![Level one](./img/level1_done.png) <br/> <br/> <br/>
</details>

<br/>

In the second level, we had to do the same than level 1, but we had an introduction to different type of masks.

![Level two](./img/level2.png)  
<details>
<summary>How to resolve level 2 ?</summary>

- Goal 1:  
We have to change the Interface A1 IP address to be between `192.168.93.193` and `104.96.23.222`. [Learn how](#network-range-and-mask) to get the range.
We also have to give the same mask for both inteface. Therfore, we have in Interface B1 the mask `255.255.255.224` or `/27`. Click [here](#mask) to learn how to convert between one and the other

- Goal 2:  
We have to change the Interface D1 IP address to be between `192.168.94.193` and `192.168.94.194`. [Learn how](#network-range-and-mask) to get the range.

![Level two](./img/level2_done.png) <br/> <br/> <br/>
</details>

<br/>

In the level 3, we now have 3 client to communicate with each other. All of them are connected to a switch.

![Level three](./img/level3.png)
<details>
<summary>How to resolve level 3 ?</summary>

- First of all we see that the mask of the network is `/25` or `255.255.255.128`. Moreover, we also know that the address `104.198.216.125` is in the network.
- Goal 1:  
We have to change both mask of Interface B1 and A1 to `/25`. [Learn more](#mask) about mask.
We alse have to change the Interface B1 IP address to be between `104.198.216.1` and `104.198.216.126`. [Learn how](#network-range-and-mask) to get the range.

- Goal 2 and 3:  
We have to change the Interface C1 IP address to be between `104.198.216.1` and `104.198.216.126`. [Learn how](#network-range-and-mask) to get the range.

![Level three](./img/level3_done.png) <br/> <br/> <br/>
</details>

<br/>

In this level 4, we had a brief introduction to interface, that will allow us to communicate to other network.

![Level four](./img/level4.png)
<details>
<summary>How to resolve level 4 ?</summary>  

The easiest for the mask is to be `/24` or `255.255.255.0`

We have to change both mask of Interface B1 and A1 to `/24`.[Learn more](#network-range-and-mask) about mask.

We alse have to change the Interface B1 IP address to be between `112.88.117.1` and `112.88.117.254`. [Learn how](#network-range-and-mask) to get the range.

All the goals should be resolved.

![Level four](./img/level4_done.png) <br/> <br/> <br/>
</details>

<br/>

In the level 5, we use this interface to make comunication between two client that are not on the same network. We have to create routes from clients to the router.

![Level five](./img/level5.png)

<details>
<summary>How to resolve level 5 ?</summary>  

The easiest for the mask is to be `/24` or `255.255.255.0`

We have to change both mask of Interface B1 and A1 to `/24`.[Learn more](#network-range-and-mask) about mask.

We alse have to change the Interface B1 IP address to be between `112.88.117.1` and `112.88.117.254`. [Learn how](#network-range-and-mask) to get the range.

All the goals should be resolved.

![Level five](./img/level5_done.png) <br/> <br/> <br/>
</details>

<br/>

In the level 6, we have an introduction to comunication between a client and an interface somewhere on the net. We take the notion learned before between client to router. In order to make the way back from internet to the client, the internet interface need to create a route toward the client router.

![Level six](./img/level6.png) <br/> <br/> <br/>

- In the level 7, we deepen into router interface. Here, we have two router that comunicate between each other, and each one of them have a connection to a client. For client A and Client C to communicate they have to create a route to their router inteface. Then both router have themselves a route to communicate between each other.

![Level seven](./img/level7.png) <br/> <br/> <br/>

- In the level 8, all we learned before is put into practice. We have to make 2 client communicate between them with an interface. Moreover they have to communicate with the an interface somewhere on the web.

![Level eight](./img/level8.png) <br/> <br/> <br/>

- In the level 9, same as level 8, everything we have learn so far is put in application.

![Level nine](./img/level9.png) <br/> <br/> <br/>

- The level ten look like the 9. It is a bit different but it put everything together from level 1 to level 7

![Level ten](./img/level10.png) <br/> <br/> <br/>

## Project Status
The project is complited

## Contact
Created by [@mliboz](https://github.com/MaxenceLiboz/) - feel free to contact me!
