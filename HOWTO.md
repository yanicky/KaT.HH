## HOW-TO:

How to run this version? Setup [HHVM]{https://hhvm.com)  you can then run it with command line client using wallet argument or served by a webserver of your choice.

#### This application default on Pirl.io public gateway if no command or endpoint is specified.
```
hhvm index.php --wallet=yourwalletaddresshere [--chain=Pirl, Ethereum, local] [--CMD=web3_clientVersion, net_version, getBalance, blockNumber, peerCount,test,howto, help] [--id=integer]
```
## Running Test

You can also run the test-api.sh like this.

From shell(external test with hhvm-cli)
```
sh test-api-hhvm.sh;
```

From your browser(New Test Sequence does not seem to be Cloudflare friendly. Investigating)

http(s)://hostname/path/to/index.php?CMD=test

#### The test should result an output SIMILAR to this:
> Starting Web test.
> Testing Wallet Only parameter
>
> {"wallet":"0x256b2b26Fe8eCAd201103946F8C603b401cE16EC","balance":"15420000.0000000000"}
>
> Testing getBalance with Pirl chain
>
> {"jsonrpc":"2.0","id":"0","result":"0xcc14fdfff1a8dad800000"}
>
> Testing getBalance with Ethereum chain
>
> {"jsonrpc":"2.0","id":"1","result":"0x0"}
>
> Testing blockNumber with Pirl chain
>
> {"jsonrpc":"2.0","id":"2","result":"0x425528"}
>
> Testing blockNumber with Ethereum chain
>
> {"jsonrpc":"2.0","id":"3","result":"0x7e5517"}
>
> Testing peerCount with Pirl chain
>
> {"jsonrpc":"2.0","id":"4","result":"0x15d"}
>
> Testing peerCount with Ethereum chain
>
> {"jsonrpc":"2.0","id":"5","result":"0xe"}
>
> Testing net_version with Pirl chain
>
> {"jsonrpc":"2.0","id":"6","result":"3125659152"}
>
> Testing net_version with Ethereum chain
>
> {"jsonrpc":"2.0","id":"7","result":"1"}
>
> Testing web3_clientVersion with Pirl chain
>
> {"jsonrpc":"2.0","id":"8","result":"Pirl/v1.8.27-v6-masternode-content-damocles-4aa88705/linux-amd64/go1.12"}
>
> Testing web3_clientVersion with Ethereum chain
>
> {"jsonrpc":"2.0","id":"9","result":"cloudflare-geth"}

Also...

This version Default on the Pirl Network(https://wallrpc.pirl.io:443) but Cloudflare's Ethereum Gateway(https://cloudflare-eth.com:443) or any other json-rpc server using --chain=[Pirl, Ethereum, local] optional parameter.

If you want to have it served by a webserver, put the files into the webroot directory and try a url syntax like these:

http(s)://hostname/path/to/index.php?chain=Pirl&CMD=blockNumber

http(s)://hostname/path/to/index.php?wallet=youraddresshere

http(s)://hostname/path/to/index.php?wallet=youraddresshere&chain=local&rpchost=localhost&rpcport=6588

http(s)://hostname/path/to/index.php?CMD=help

Feel free to add pull requests or fork it for your own usage.
