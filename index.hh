<?hh
// Tested with HHVM
//
// require php-curl to be installed/enabled.

// Set Error Level
error_reporting(0);

require __DIR__ . '/vendor/hh_autoload.hh';
use namespace Facebook\Markdown;

function render(string $markdown): string {
  $ast = Markdown\parse(new Markdown\ParserContext(), $markdown);

  $html = (new Markdown\HTMLRenderer(
    new Markdown\RenderContext()
  ))->render($ast);

  return $html;
}


function jsonCurl($myurl, $mymethod, $mypayload) 
        {
	//create a new cURL resource
	$ch = curl_init($myurl);
	curl_setopt($ch, CURLOPT_POST, TRUE);
	//attach encoded JSON string to the POST fields
	curl_setopt($ch, CURLOPT_POSTFIELDS, $mypayload);
	//set the content type to application/json
	curl_setopt($ch, CURLOPT_HTTPHEADER, array('Content-Type:application/json'));
	//return response instead of outputting
	curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
	//execute the POST request
	$res = curl_exec($ch);
	//close cURL resource
	curl_close($ch);
	//return the result
	return $res;
	}

// To be used with php-cli in console (ie: php index.php --wallet=yourwalletaddresshere)
foreach( $argv as $argument ) {
        if( $argument == $argv[ 0 ] ) continue;

        $pair = explode( "=", $argument );
        $variableName = substr( $pair[ 0 ], 2 );
        $variableValue = $pair[ 1 ];
        //echo $variableName . " = " . $variableValue . "\n";
        // Optionally store the variable in $_REQUEST
        $_REQUEST[ $variableName ] = $variableValue;
	$envvariable = $variableName . "=" . $variableValue;
	putenv($envvariable);
	//echo getenv($variableName);
}

// Create NewLine variable based on usage
if ($argc > 0) {$NL = "\n"; $RUNMODE = "php-cli";} else {$NL = "</br>"; $RUNMODE = "webserv";}

//if requested, setup variables

if(getenv("id")){
$ID = getenv("id");
}
if(getenv("CMD")){
$CMD = getenv("CMD");
}
if(getenv("chain")){
$CHAIN = getenv("chain");
}
if(getenv("wallet")){
$addr = getenv("wallet");
}
if(getenv("rpchost")){
$RPCHOST = getenv("rpchost");
}
if(getenv("rpcport")){
$RPCPORT = getenv("rpcport");
}
if(getenv("block")){
$BLOCK = getenv("block");
}

// If Required uncomment/force some parameters here
//$addr = "yourwallethere";
//$CMD = "getBalance";
//$CHAIN = "local";

// The RPCHOST and RPCPORT only override settings if($CHAIN == "local").
// Forced by default to pirl local node.
// Comment out the following to allow --rpchost and --rpcport. Handle with care as it open to possible abuse if used on webservers.
$RPCHOST = "localhost";
$RPCPORT = 6588;
//

//pass some simple sanity checks
if (!$CMD){ $CMD = "getDecodedBalance";}
if (!$ID){ $ID = "0";}

switch($CHAIN){
 case "Pirl":
	//pirls official rpc server, made for things like this
	$url = 'https://wallrpc.pirl.io';
	break;

 case "Ethereum":
	//use --chain=Ethereum to connect to the cloudFlare Ethereum RPC Gateway
	$url = 'https://cloudflare-eth.com';
	break;
 case "local":
	//use this if your running a local pirl node (be sure to start it up with --rpc after the command)
	// rpchost AND rpcport are required in order to FORCE to use on other server.
	if(!$RPCHOST){ $RPCHOST = "localhost";}
	if(!$RPCPORT){ $RPCPORT = "6588";}	
	$url = 'http://' . $RPCHOST . ':' . $RPCPORT;
	break;

default:
	
	$CHAIN="Pirl";
        $url = 'https://wallrpc.pirl.io';
	break;
}
        break;
	
	case "eth_getBlockByNumber":
        $method = "eth_getBlockByNumber";
        $params = [$BLOCK, true];
        //setup request to send json via POST
        $data = array();
        $data['jsonrpc'] = "2.0";
        $data['id'] = $ID;
        $data['method'] = $method;
        $data['params'] = $params;
        $payload = json_encode($data);
        //do the call
        $jsondata = jsonCurl($url, $method, $payload);
        break;
		
	case "eth_getBlockByHash":
        $method = "eth_getBlockByHash";
        $params = [$BLOCK, true];
        //setup request to send json via POST
        $data = array();
        $data['jsonrpc'] = "2.0";
        $data['id'] = $ID;
        $data['method'] = $method;
        $data['params'] = $params;
        $payload = json_encode($data);
        //do the call
        $jsondata = jsonCurl($url, $method, $payload);
        break;
		
	case "getBalance":
	// verify validity of the required variables
	if ( $addr == "" ) {echo "url should be in format 'http(s)://hostname/path/to/index.php?wallet=youraddresshere' or using --wallet=yourwallethere from php-cli" . $NL; exit;}
	if ( strlen($addr) != "42" ) { echo "wallet should be 42 char, including the 0x beginning" . $NL; exit;}
	$method = "eth_getBalance";
	$params = array($addr, "latest");
	//setup request to send json via POST
        $data = array();
        $data['jsonrpc'] = "2.0";
        $data['id'] = $ID;
        $data['method'] = $method;
        $data['params'] = $params;
        $payload = json_encode($data);
        //do the call
        $jsondata = jsonCurl($url, $method, $payload);

	break;
	
	case "getDecodedBalance":
        // verify validity of the required variables
        if ( $addr == "" ) {echo "url should be in format 'http(s)://hostname/path/to/index.php?wallet=youraddresshere' or using --wallet=yourwallethere from php-cli" . $NL . "Address is: " . $addr . $NL; exit;}
        if ( strlen($addr) != "42" ) { echo "wallet should be 42 char, including the 0x beginning" . $NL; exit;}
        $method = "eth_getBalance";
        $params = array($addr, "latest");
        //setup request to send json via POST
        $data = array();
        $data['jsonrpc'] = "2.0";
        $data['id'] = $ID;
        $data['method'] = $method;
        $data['params'] = $params;
        $payload = json_encode($data);
        //do the call
        $jsondata1 = json_decode(jsonCurl($url, $method, $payload), false);
        $balance_val = $jsondata1->result;
        $pirl = number_format((hexdec($balance_val)/1000000000000000000), 10, ".", "");
        $assocArray = array();
        $assocArray['wallet'] = ''.$addr.'';
        $assocArray['balance'] = ''.$pirl.'';
	//encode in json format
	$jsondata = json_encode($assocArray);

        break;

	case "help":
	echo "********************" . $NL;
	echo "Printing Help" . $NL. $NL;
	echo "options are CMD=[net_version, getBalance, blockNumber, peerCount], chain=[Pirl, Ethereum, local], [rpchost=IP, Hostname] and [rpcport=PortNum]" . $NL;
	echo "ie: php index.php --CMD=blockNumber --chain=Pirl" . $NL;
	echo "url syntax examples when using a web server:" . $NL;
	echo "http(s)://hostname/path/to/index.php?chain=Pirl&CMD=blockNumber" . $NL;
	echo "http(s)://hostname/path/to/index.php?wallet=youraddresshere" . $NL;
	echo "http(s)://hostname/path/to/index.php?wallet=youraddresshere&chain=local&rpchost=localhost&rpcport=6588" . $NL;
	echo "http(s)://hostname/path/to/index.php?CMD=help" . $NL;
	break;
		
	case "test":
        if($RUNMODE == "php-cli"){
        echo "Running test from console, please check HOWTO.md for details". $NL;       
        } else {
	include('test/testweb.php');
	
	if($test!=""){echo $test;}else{ echo "No test results";}
	}
	break;
	
	case "readme":
        //echo "We are in Howto:" .$NL;
        $markdown = file_get_contents('https://raw.githubusercontent.com/yanicky/KaT/master/README.md');
        
        if($RUNMODE == "php-cli"){
		echo $markdown;
	} else {
        	echo render($markdown);
	}
        break;
		
	case "howto":
        //echo "We are in Howto:" .$NL;
        $markdown = file_get_contents('https://raw.githubusercontent.com/yanicky/KaT/master/HOWTO.md');
        
        if($RUNMODE == "php-cli"){
		echo $markdown;
	} else {
        	echo render($markdown);
	}
        break;

	default: 
	echo "********************" . $NL;
	echo "Error: CMD value is invalid." . $NL; 
	echo "please use --CMD=help for more details" . $NL;
	break;
}
//finally, echo result of the work.
if($jsondata!=""){echo $jsondata;}
