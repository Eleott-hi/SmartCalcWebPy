<script setup>
import WelcomeItem from './WelcomeItem.vue'
import IconBaseCalculator from './icons/IconBaseCalculator.vue'
import IconAdvancedCalculator from './icons/IconAdvancedCalculator.vue'
import IconPlot from './icons/IconPlot.vue'
import IconDeposit from './icons/IconDeposit.vue'
import IconLoan from './icons/IconLoan.vue'
import IconSupport from './icons/IconSupport.vue'
</script>

<template>
  <div>
    <WelcomeItem>
      <template #icon>
        <IconBaseCalculator />
      </template>
      <template #heading>Performing Arithmetic Operations</template>
      <RouterLink :to="{ name: 'calculator' }">SmartCalcWeb</RouterLink>
      supports basic arithmetic operations, including addition, subtraction, multiplication, and division.
      Simply type your expression in the input field and press Enter to get the result instantly.
    </WelcomeItem>

    <WelcomeItem>
      <template #icon>
        <IconAdvancedCalculator />
      </template>
      <template #heading>Handling Complex Expressions</template>
      Need to solve complex mathematical expressions?
      <RouterLink :to="{ name: 'calculator' }">SmartCalcWeb</RouterLink>
      can handle it all. Use parentheses, exponents, square
      roots, and more to create intricate calculations with ease.
    </WelcomeItem>

    <WelcomeItem>
      <template #icon>
        <IconPlot />
      </template>
      <template #heading>Function Plotting</template>
      Visualize mathematical functions in 2D with
      <RouterLink :to="{ name: 'plot' }">SmartCalcWeb’s plotting</RouterLink>
      feature. Enter the function, specify the range,
      and see the graph come to life. Perfect for students, educators, and professionals who need to illustrate
      mathematical
      concepts.
    </WelcomeItem>

    <WelcomeItem>
      <template #icon>
        <IconLoan />
      </template>
      <template #heading>Loan Calculations</template>
      SmartCalcWeb’s
      <RouterLink :to="{ name: 'loan_calculator' }"> loan calculator </RouterLink>
      helps you plan your finances effectively. Input the loan amount, interest rate, and
      duration to calculate monthly payments and total interest. Stay informed about your financial commitments
      effortlessly.
    </WelcomeItem>

    <WelcomeItem>
      <template #icon>
        <IconDeposit />
      </template>
      <template #heading>Deposit Calculations</template>

      Planning to save for the future? SmartCalcWeb’s
      <RouterLink :to="{ name: 'deposit_calculator' }"> deposit calculator </RouterLink>
      assists you in understanding the growth of your
      savings. Input the initial deposit, interest rate, and time period to visualize your savings’ potential.

    </WelcomeItem>

    <WelcomeItem>
      <template #icon>
        <IconSupport />
      </template>
      <template #heading>Support and Feedback</template>
      Encountered an issue or need assistance? Our support team is ready to help. Contact
      <a href="https://github.com/Eleott-hi/SmartCalcWebPy"> us </a>
      for prompt and friendly assistance.
      <br>
      <br>
      We value your feedback! If you have suggestions for improvements or new features,
      please contact
      <a href="https://github.com/Eleott-hi/SmartCalcWebPy"> us </a>
      . Your input helps us make SmartCalcWeb even better.
      <br>
      <br>
      <RouterLink :to="{ name: 'calculator' }"> SmartCalcWeb </RouterLink>
      is more than just a calculator. It’s your smart choice for swift and accurate calculations. Start
      exploring its powerful features today and experience mathematics like never before!
    </WelcomeItem>
  </div>
</template>
