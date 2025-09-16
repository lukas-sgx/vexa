<?php 
    require_once '../include/db.php';

    if(isset($_POST)){
        
        function getSolde($number) {
            $db = getDBConnection();

            $query = "SELECT `solde` FROM user WHERE `number` = :username";
            $stmt = $db->prepare($query);
            $stmt->bindParam(':username', $number);
            $stmt->execute();

            $info = $stmt->fetch(PDO::FETCH_ASSOC);

            return $info["solde"];
        }

        if($_POST['cmd'] == "getSold"){
            $solde = getSolde($_POST["number"]);

            $myObj = new stdClass();
            $myObj->solde = $solde;

            echo json_encode($myObj);
        }
    }