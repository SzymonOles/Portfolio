var express = require('express');
var router = express.Router();

const katalogController = require('../controllers/katalogController');

router.get('/', katalogController.getMain);

module.exports = router;
