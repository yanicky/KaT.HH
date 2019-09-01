#!/bin/bash
echo "Testing without parameters";
hhvm index.hh;
echo "***";
echo "Testing with bad wallet only parameters";
hhvm index.hh --wallet=0x256b2b26Fe8eCAd201103946F8C603b401cE16E;
echo "***";
echo "Testing with good wallet parameters only with default parameter";
hhvm index.hh --wallet=0x256b2b26Fe8eCAd201103946F8C603b401cE16EC;
echo "***";
echo "Testing getBalance with Ethereum chain"; 
hhvm index.hh --CMD=getBalance --wallet=0x256b2b26Fe8eCAd201103946F8C603b401cE16EC --chain=Ethereum --id=1;
echo "***";
echo "Testing getBalance with bad chain parameter";
hhvm index.hh --CMD=getBalance --wallet=0x256b2b26Fe8eCAd201103946F8C603b401cE16EC --chain=Ethereu --id=2;
echo "***";
echo "Testing blockNumber with Pirl chain";
hhvm index.hh --chain=Pirl --CMD=blockNumber --id=3;
echo "***";
echo "Testing blockNumber with Ethereum chain";
hhvm index.hh --chain=Ethereum --CMD=blockNumber --id=4;
echo "***";
echo "Testing peerCount with default chain";
hhvm index.hh --CMD=peerCount --id=5;
echo "***";
echo "Testing peerCount with Ethereum chain";
hhvm index.hh --CMD=peerCount --chain=Ethereum --id=6;
echo "***";
echo "Testing net_version with default chain";
hhvm index.hh --CMD=net_version --chain=Pirl --id=7
echo "***";
echo "Testing net_version with Ethereum chain";
hhvm index.hh --CMD=net_version --chain=Ethereum --id=8
echo "***";
echo "Testing client_version with Default chain";
hhvm index.hh --CMD=web3_clientVersion --id=9
echo "***";
echo "Testing client_version with Ethereum chain";
hhvm index.hh --CMD=web3_clientVersion --chain=Ethereum --id=10
echo "***";
echo "";
