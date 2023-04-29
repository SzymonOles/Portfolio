var express = require('express');
var router = express.Router();

const informacjeController = require('../controllers/informacjeController');

router.get('/', informacjeController.getMain);

module.exports = router;
