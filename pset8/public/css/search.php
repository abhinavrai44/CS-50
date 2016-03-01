<?php

    require(__DIR__ . "/../includes/config.php");
	
    // get the parameters and then modify it
	$code = urldecode($_GET["geo"]);
	$ex = explode(",", $code);
	//print("COde : ".$code."\n");
	//for ($i = 0; $i < count($ex); $i++)
	//print("ex : ".$ex[$i]."\n");
    $params = array_map('trim', $ex);
	//for ($i = 0; $i < count($params); $i++)
	//print("1. Paramas : ".$params[$i]." p\n");
    
    // remove "IN" param, as all addresses are IN
    if (($index = array_search("IN", $params)) !== false) {
        unset($params[$index]);
    }

    if (($index = array_search("in", $params)) !== false) {
        unset($params[$index]);
    }    
    
	//for ($i = 0; $i < count($params); $i++)
	//print("2. Paramas : ".$params[$i]." p\n");

    // SQL statement
    $sql = "SELECT * FROM places WHERE ";
	$count = count($params);
	//print("Count : ".$count." \n");

    for ($i = 0; $i < $count; $i++) {
        // if param is numeric, assume a postal code
        if (is_numeric($params[$i])) {
            $sql .= 'postal_code LIKE "' . htmlspecialchars($params[$i], ENT_QUOTES) . '%"';
        } else {
            $sql .= 
                '(place_name  LIKE "' . htmlspecialchars($params[$i], ENT_QUOTES) . '%" OR ' . 
                 (strlen($params[$i]) <= 2 ? 'admin_code1 LIKE "' . htmlspecialchars($params[$i], ENT_QUOTES) . '%" OR ' : "") . 
                 'admin_name1 LIKE "' . htmlspecialchars($params[$i], ENT_QUOTES) . '%")';
        }
        //print("Sql : ".$sql."\n");
        if ($i < ($count - 1)) {
            $sql .= " AND ";
        }
    }

	//print("Sql : ".$sql."\n");

    // search the database
    $places = query($sql);
    
    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>
